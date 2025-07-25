#include <math.h>
#include "pico/stdlib.h"

#define AUDIO_PIN 0
#define LED_PIN 25

void play_square(uint gpio, uint base_freq, int duration_ms, int vibrato = 0) {
    const uint32_t start = to_ms_since_boot(get_absolute_time());

    gpio_set_function(gpio, GPIO_FUNC_SIO);
    gpio_set_dir(gpio, GPIO_OUT);

    while (to_ms_since_boot(get_absolute_time()) - start < (uint32_t)duration_ms) {
        // Apply simple vibrato
        int time_ms = to_ms_since_boot(get_absolute_time()) - start;
        float mod = 1.0 + 0.05f * sinf(6.28f * time_ms / 100.0f);  // slow vibrato
        float freq = base_freq * (1.0 + vibrato * (mod - 1.0f));
        uint32_t delay_us = 1000000.0f / (freq * 2.0f);

        gpio_put(gpio, true);
        sleep_us(delay_us);
        gpio_put(gpio, false);
        sleep_us(delay_us);
    }

    gpio_put(gpio, false);  // ensure quiet output
}

void mute_audio(const uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_SIO);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, false);
}

[[noreturn]] int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Chiptune-style melody: C E G A G E C
    const int notes[] = {262, 330, 392, 440, 392, 330, 262};
    constexpr int count = sizeof(notes) / sizeof(notes[0]);
    const int durations[] = {150, 150, 150, 300, 150, 150, 300};

    while (true) {
        for (int i = 0; i < count; i++) {
            gpio_put(LED_PIN, 1);
            play_square(AUDIO_PIN, notes[i], durations[i], 1);  // vibrato on
            gpio_put(LED_PIN, 0);
            mute_audio(AUDIO_PIN);
            sleep_ms(50);
        }
        mute_audio(AUDIO_PIN);
        sleep_ms(600);  // pause between loops
    }
}
