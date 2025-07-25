// test/pico/tone_player.cpp
#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/audio_pwm.h"
#include "hardware/gpio.h"

// Configuration
#define SAMPLE_RATE 22050
#define BUFFER_SIZE 512
#define PWM_PIN 0
#define TONE_FREQ 440
#define DURATION_MS 10000  // 10 seconds playback time

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

int main() {
    stdio_init_all();
    printf("Sine Wave Audio PWM Player Starting...\n");
    sleep_ms(2000);  // Wait for console to connect

    // Set up LED for visual feedback
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);  // Turn on LED to show we've started

    // Audio format for PWM
    audio_format_t audio_format;
    audio_format.sample_freq = SAMPLE_RATE;
    audio_format.format = AUDIO_BUFFER_FORMAT_PCM_S16;
    audio_format.channel_count = 1;

    // Audio buffer format
    audio_buffer_format_t producer_format;
    producer_format.format = &audio_format;
    producer_format.sample_stride = 2;  // 16-bit = 2 bytes per sample

    // PWM channel config
    audio_pwm_channel_config_t channel_config;
    channel_config.core.base_pin = PWM_PIN;
    printf("Setting up audio PWM on pin %d...\n", PWM_PIN);
    if (!audio_pwm_setup(&audio_format, -1, &channel_config)) {
        printf("Failed to initialize PWM audio\n");
        return -1;
    }

    printf("Creating buffer pool...\n");
    audio_buffer_pool_t* producer_pool = audio_new_producer_pool(&producer_format, 3, BUFFER_SIZE);
    if (!producer_pool) {
        printf("Failed to create audio buffer pool\n");
        return -1;
    }

    printf("Connecting PWM...\n");
    if (!audio_pwm_default_connect(producer_pool, false)) {
        printf("Failed to connect PWM\n");
        return -1;
    }

    printf("Enabling PWM output...\n");
    audio_pwm_set_enabled(true);
    printf("Playing %dHz sine wave tone for %d ms...\n", TONE_FREQ, DURATION_MS);

    // Use slightly reduced amplitude for cleaner sound
    const int16_t AMPLITUDE = 25000;
    float phase = 0.0f;
    uint32_t start_time = to_ms_since_boot(get_absolute_time());
    while (to_ms_since_boot(get_absolute_time()) - start_time < DURATION_MS) {
        // Blink LED while playing for visual feedback
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        audio_buffer_t* buffer = take_audio_buffer(producer_pool, true);
        int16_t* samples = (int16_t*)buffer->buffer->bytes;
        // Fill the buffer with a sine wave - much more pleasant than square wave
        for (uint i = 0; i < BUFFER_SIZE; i++) {
            // Create smooth sine wave
            float t = (float)i / SAMPLE_RATE;
            // Apply envelope (fade in/out) to reduce clicks
            float envelope = 1.0f;
            uint32_t time_elapsed = to_ms_since_boot(get_absolute_time()) - start_time;
            // Fade in during first 100ms
            if (time_elapsed < 100) {
                envelope = time_elapsed / 100.0f;
            }
            // Fade out during last 500ms
            else if (time_elapsed > DURATION_MS - 500 && DURATION_MS > 500) {
                envelope = (DURATION_MS - time_elapsed) / 500.0f;
            }
            samples[i] = (int16_t)(AMPLITUDE * envelope * sinf(2.0f * M_PI * TONE_FREQ * (t + phase)));
        }

        // Maintain phase continuity between buffers
        phase += (float)BUFFER_SIZE / SAMPLE_RATE;
        if (phase >= 1.0f) {
            phase -= 1.0f;  // Keep phase in [0,1) range to prevent float precision issues
        }

        buffer->sample_count = BUFFER_SIZE;
        give_audio_buffer(producer_pool, buffer);

        // Print status every second
        if ((to_ms_since_boot(get_absolute_time()) - start_time) % 1000 < 10) {
            printf("Still playing sine wave at %dHz...\n", TONE_FREQ);
        }
    }

    // Clean up
    printf("Tone finished\n");
    audio_pwm_set_enabled(false);

    // Turn off LED
    gpio_put(LED_PIN, 0);

    // Sleep to ensure all audio is played before shutdown
    sleep_ms(500);

    printf("Done!\n");
    return 0;
}