#include <cmath>
#include <cstdio>
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "pico/pico_audio_pwm.h"

#define AUDIO_PIN 0
#define SAMPLE_RATE 22050
#define BUFFER_SIZE 256

// A simple 8-bit sine wave lookup table
uint8_t sine_wave[BUFFER_SIZE];

void fill_sine_wave() {
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        float theta = 2.0f * 3.14159265f * i / BUFFER_SIZE;
        sine_wave[i] = (uint8_t)((sinf(theta) * 127.5f) + 127.5f); // 0-255
    }
}

int main() {
    stdio_init_all();

    printf("Raw PWM PIO Audio Test\n");

    fill_sine_wave();

    // Load the PIO program
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &pico_audio_pwm_program);

    pico_audio_pwm_program_init(pio, sm, offset, AUDIO_PIN);

    // Set PWM clock to match sample rate
    float clk_div = (float)clock_get_hz(clk_sys) / (SAMPLE_RATE * 32);
    pio_sm_set_clkdiv(pio, sm, clk_div);

    // Start streaming samples (forever)
    while (true) {
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            // 8-bit -> 32-bit left-justified (bitshifted by 24)
            pio_sm_put_blocking(pio, sm, sine_wave[i] << 24);
        }
    }
}
