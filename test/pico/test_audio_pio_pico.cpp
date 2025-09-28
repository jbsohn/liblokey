#include <cmath>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "audio_pwm.pio.h"
#include "pico/bootrom.h"

constexpr int AUDIO_PIN = 18;
constexpr int SM = 0;
constexpr  int LED_PIN = 25;

void pwm_one_bit_dither_program_init(PIO pio, uint sm, uint offset, uint pin) {
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    pio_sm_config c = pwm_one_bit_dither_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_clkdiv(&c, 1.0f);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}

void playSquarePio(PIO pio, uint sm, uint base_freq, int duration_ms, int vibrato = 0) {
    const uint32_t start = to_ms_since_boot(get_absolute_time());

    while (to_ms_since_boot(get_absolute_time()) - start < static_cast<uint32_t>(duration_ms)) {
        const int time_ms = to_ms_since_boot(get_absolute_time()) - start;
        const float mod = 1.0f + 0.05f * sinf(6.28f * time_ms / 100.0f);  // slow vibrato
        const float freq = base_freq * (1.0 + vibrato * (mod - 1.0f));
        const uint32_t delay_us = 1000000.0f / (freq * 2.0f);

        // HIGH
        if (pio_sm_is_tx_fifo_empty(pio, sm)) {
            pio_sm_put_blocking(pio, sm, 0xFFFF);
        }
        sleep_us(delay_us);

        // LOW
        if (pio_sm_is_tx_fifo_empty(pio, sm)) {
            pio_sm_put_blocking(pio, sm, 0x0000);
        }
        sleep_us(delay_us);
    }
    // Silence at end
    if (pio_sm_is_tx_fifo_empty(pio, sm)) {
        pio_sm_put_blocking(pio, sm, 0x0000);
    }
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    const PIO pio = pio0;
    const uint offset = pio_add_program(pio, &pwm_one_bit_dither_program);  // <- your program name
    pwm_one_bit_dither_program_init(pio, SM, offset, AUDIO_PIN);

    // Melody: C E G A G E C
    const int notes[] = {262, 330, 392, 440, 392, 330, 262};
    constexpr int count = sizeof(notes) / sizeof(notes[0]);
    const int durations[] = {150, 150, 150, 300, 150, 150, 300};

    for (int i = 0; i < count; i++) {
        gpio_put(LED_PIN, true);
        playSquarePio(pio, SM, notes[i], durations[i], 1);  // vibrato on
        gpio_put(LED_PIN, false);
        if (pio_sm_is_tx_fifo_empty(pio, SM)) {
            pio_sm_put_blocking(pio, SM, 0x0000);
        }
        sleep_ms(50);
    }

    // Fully mute PWM output, disable PIO SM
    if (pio_sm_is_tx_fifo_empty(pio, SM)) {
        pio_sm_put_blocking(pio, SM, 0x0000);
    }

    sleep_ms(600);  // pause between loops
    reset_usb_boot(0, 0);
}
