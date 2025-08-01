#include "pico_gpio_audio_sink.hpp"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <cstring>

PicoGpioAudioSink::PicoGpioAudioSink(const uint gpio_pin, const uint32_t sample_rate)
    : gpio_pin(gpio_pin), sample_rate(sample_rate) {
    queue_init(&sampleQueue, sizeof(int16_t) * kBufferSize, kQueueLength);
}

PicoGpioAudioSink::~PicoGpioAudioSink() {
    PicoGpioAudioSink::stop();
    queue_free(&sampleQueue);
    gpio_put(gpio_pin, false);
}

void PicoGpioAudioSink::start() {
    if (running)
        return;
    running = true;
    multicore_launch_core1(core1Task);
    multicore_fifo_push_blocking(reinterpret_cast<uintptr_t>(this));
}

void PicoGpioAudioSink::stop() {
    if (!running) {
        return;
    }
    running = false;
}

void PicoGpioAudioSink::writeAudio(const std::span<const int16_t> samples) {
    if (!running || samples.empty()) {
        return;
    }

    size_t offset = 0;
    while (offset < samples.size()) {
        int16_t buffer[kBufferSize] = {};
        const size_t chunk = std::min<size_t>(kBufferSize, samples.size() - offset);
        std::memcpy(buffer, samples.data() + offset, chunk * sizeof(int16_t));
        queue_add_blocking(&sampleQueue, buffer);
        offset += chunk;
    }
}

void PicoGpioAudioSink::core1Task() {
    auto* sink = reinterpret_cast<PicoGpioAudioSink*>(multicore_fifo_pop_blocking());
    if (sink == nullptr) {
        return;
    }

    gpio_init(sink->gpio_pin);
    gpio_set_dir(sink->gpio_pin, GPIO_OUT);
    gpio_put(sink->gpio_pin, false);

    int16_t buffer[kBufferSize];

    while (sink->running) {
        queue_remove_blocking(&sink->sampleQueue, buffer);
        const float us_per_sample = 1'000'000.0f / static_cast<float>(sink->sample_rate);
        for (const short i : buffer) {
            gpio_put(sink->gpio_pin, i >= 0);
            sleep_us(static_cast<uint32_t>(us_per_sample));
            if (!sink->running) {
                break;
            }
        }
    }
    gpio_put(sink->gpio_pin, false);
}
