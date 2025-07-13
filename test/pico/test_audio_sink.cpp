#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "atari800_pokey.hpp"
#include "pico_audio_sink.hpp"
#include "hardware/pwm.h"

void playTone(Pokey& pokey, AudioSink& sink, const uint8_t audf, const uint8_t audc, const int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf, 1);
    pokey.poke(PokeyRegister::AUDC1, audc, 1);

    const absolute_time_t end = make_timeout_time_ms(ms);
    while (!time_reached(end)) {
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
        sleep_ms(4);
    }
}

void flash() {
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(1000);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(1000);
}

int main() {
    stdio_init_all();
    printf("Running Atari800 POKEY + Pico AudioSink test...\n");

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    flash();
    sleep_ms(2000);

    PicoAudioSink sink(44100, 0);
    Atari800Pokey pokey(44100, 512, 0);

    sink.start();

    // Soft tone 1
    pokey.poke(PokeyRegister::AUDCTL, 0x00, 1);
    pokey.poke(PokeyRegister::AUDC1, 0xA2, 1);
    playTone(pokey, sink, 0x50, 0xA2, 800);
    // Soft tone 2
    playTone(pokey, sink, 0x30, 0xA4, 800);
    // Soft tone 3
    playTone(pokey, sink, 0x20, 0xA6, 800);

    // Silence
    pokey.poke(PokeyRegister::AUDC1, 0x00, 1);
    sleep_ms(500);

    printf("Done.\n");
    return 0;
}
