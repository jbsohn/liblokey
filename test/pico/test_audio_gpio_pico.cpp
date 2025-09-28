#include <cmath>
#include <cstdio>
#include "pico/stdlib.h"
#include "pico/bootrom.h"

constexpr int AUDIO_PIN = 18;
constexpr int LED_PIN = 25;

void playSquare(const uint gpio, const uint base_freq, const int duration_ms, const int vibrato = 0) {
    const uint32_t start = to_ms_since_boot(get_absolute_time());

    gpio_set_function(gpio, GPIO_FUNC_SIO);
    gpio_set_dir(gpio, GPIO_OUT);

    while (to_ms_since_boot(get_absolute_time()) - start < (uint32_t)duration_ms) {
        // Apply simple vibrato
        const int time_ms = to_ms_since_boot(get_absolute_time()) - start;
        const float mod = 1.0f + 0.05f * sinf(6.28f * time_ms / 100.0f);  // slow vibrato
        const float freq = base_freq * (1.0 + vibrato * (mod - 1.0f));
        const uint32_t delay_us = 1000000.0f / (freq * 2.0f);

        gpio_put(gpio, true);
        sleep_us(delay_us);
        gpio_put(gpio, false);
        sleep_us(delay_us);
    }

    gpio_put(gpio, false);  // ensure quiet output
}

void muteAudio(const uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_SIO);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, false);
}

int main() {
    stdio_init_all();
    printf("starting audio test\n");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Chiptune-style melody: C E G A G E C
    const int notes[] = {262, 330, 392, 440, 392, 330, 262};
    constexpr int count = sizeof(notes) / sizeof(notes[0]);

    for (int i = 0; i < count; i++) {
        const int durations[] = {150, 150, 150, 300, 150, 150, 300};
        gpio_put(LED_PIN, true);
        playSquare(AUDIO_PIN, notes[i], durations[i], 1);  // vibrato on
        gpio_put(LED_PIN, false);
        muteAudio(AUDIO_PIN);
        sleep_ms(50);
    }
    muteAudio(AUDIO_PIN);
    reset_usb_boot(0, 0);
}
