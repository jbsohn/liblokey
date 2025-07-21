// pico_audio_sink.cpp
#include "pico_audio_sink.hpp"
#include "pico/stdlib.h"
#include "pico/audio_pwm.h"
#include <memory.h>
#include <stdio.h>

// Static member to support callback
PicoAudioSink* PicoAudioSink::active_instance = nullptr;

PicoAudioSink::PicoAudioSink(const uint gpio, const uint sampleRate, const uint bufferSize)
    : gpio(gpio), sampleRate(sampleRate), bufferSize(bufferSize) {
    // Initialize the queue for sample buffers (pointers)
    queue_init(&sampleQueue, sizeof(int16_t*), 10);  // Queue of pointers, not samples
}

PicoAudioSink::~PicoAudioSink() {
    stop();
    // Clean up any remaining buffers in the queue
    int16_t* buffer;
    while (queue_try_remove(&sampleQueue, &buffer)) {
        delete[] buffer;
    }
    queue_free(&sampleQueue);
}

void PicoAudioSink::start() {
    if (running.exchange(true)) {
        return;  // Already running
    }
    // Set up audio format
    audio_format_t audio_format;
    audio_format.sample_freq = sampleRate;
    audio_format.format = AUDIO_BUFFER_FORMAT_PCM_S16;
    audio_format.channel_count = 1;
    // Audio buffer format
    audio_buffer_format = {};
    audio_buffer_format.format = &audio_format;
    audio_buffer_format.sample_stride = 2;  // 16-bit = 2 bytes per sample
                                            // PWM channel config
    audio_pwm_channel_config_t channel_config = {};
    channel_config.core.base_pin = static_cast<uint8_t>(gpio);
    printf("Setting up audio PWM on pin %d...\n", gpio);
    if (!audio_pwm_setup(&audio_format, -1, &channel_config)) {
        printf("Failed to initialize PWM audio\n");
        running.store(false);
        return;
    }
    printf("Creating buffer pool...\n");
    buffer_pool = audio_new_producer_pool(&audio_buffer_format, 3, bufferSize);
    if (!buffer_pool) {
        printf("Failed to create audio buffer pool\n");
        running.store(false);
        return;
    }
    printf("Connecting PWM...\n");
    if (!audio_pwm_default_connect(buffer_pool, false)) {
        printf("Failed to connect PWM\n");
        running.store(false);
        return;
    }
    printf("Enabling PWM output...\n");
    audio_pwm_set_enabled(true);
    // Start core1 for audio processing
    active_instance = this;
    multicore_launch_core1(core1Task);
}

void PicoAudioSink::stop() {
    if (!running.exchange(false)) {
        return;  // Not running
    }
    // Wait for core1 to exit
    sleep_ms(100);
    // Disable PWM audio
    audio_pwm_set_enabled(false);
    // Clean up any remaining buffers in the queue
    int16_t* buffer;
    while (queue_try_remove(&sampleQueue, &buffer)) {
        delete[] buffer;
    }
}

void PicoAudioSink::writeAudio(tcb::span<const int16_t> samples) {
    // Process samples in chunks of bufferSize
    size_t offset = 0;
    while (offset < samples.size()) {
        // Calculate how many samples to process in this iteration
        size_t chunk_size = std::min(bufferSize, samples.size() - offset);
        // Allocate buffer for queue - this must persist until playbackLoop uses it
        auto* buffer = new int16_t[bufferSize];
        if (!buffer) {
            printf("Failed to allocate audio buffer\n");
            return;
        }
        // Copy the samples
        memcpy(buffer, samples.data() + offset, chunk_size * sizeof(int16_t));
        // Zero-fill any remaining buffer space if chunk is smaller than buffer
        if (chunk_size < bufferSize) {
            memset(buffer + chunk_size, 0, (bufferSize - chunk_size) * sizeof(int16_t));
        }
        // Scale volume if needed
        if (volume != 1.0f) {
            for (size_t i = 0; i < chunk_size; i++) {
                buffer[i] = static_cast<int16_t>(buffer[i] * volume);
            }
        }
        // Add to queue, blocking if full
        queue_add_blocking(&sampleQueue, &buffer);  // Queue the pointer to buffer
        offset += chunk_size;
    }
}

void PicoAudioSink::core1Task() {
    if (active_instance) {
        active_instance->playbackLoop();
    }
}

void PicoAudioSink::playbackLoop() {
    while (running.load()) {
        // Get next buffer pointer from queue
        int16_t* buffer;
        if (queue_try_remove(&sampleQueue, &buffer)) {
            // Get a free audio buffer
            audio_buffer_t* audio_buffer = take_audio_buffer(buffer_pool, true);
            if (audio_buffer) {
                // Copy our samples to the audio buffer
                memcpy(audio_buffer->buffer->bytes, buffer, bufferSize * sizeof(int16_t));
                audio_buffer->sample_count = bufferSize;

                // Free the buffer now that we've copied it
                delete[] buffer;

                // Send the buffer for playback
                give_audio_buffer(buffer_pool, audio_buffer);
            } else {
                // No audio buffer available, try again later
                queue_add_blocking(&sampleQueue, &buffer);
                sleep_ms(1);
            }
        } else {
            // No data available, output silence
            audio_buffer_t* audio_buffer = take_audio_buffer(buffer_pool, true);
            if (audio_buffer) {
                // Fill with zeros (silence)
                memset(audio_buffer->buffer->bytes, 0, bufferSize * sizeof(int16_t));
                audio_buffer->sample_count = bufferSize;
                give_audio_buffer(buffer_pool, audio_buffer);
            }
            sleep_ms(1);
        }
    }
}