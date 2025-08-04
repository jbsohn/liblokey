#include <cstdio>
#ifdef PICO_ON_DEVICE
#include "pico/time.h"
#else
#include <chrono>
#include <thread>
#endif

#include "pokey.hpp"
#include "audio_sink.hpp"
#include "test_audio_sink_a800.hpp"
#include "pokey_register.hpp"

#include <thread>

inline uint64_t now_ms() {
#ifdef PICO_ON_DEVICE
    return to_ms_since_boot(get_absolute_time());
#else
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
#endif
}

inline void delay_ms(uint32_t ms) {
#ifdef PICO_ON_DEVICE
    sleep_ms(ms);  // Provided by pico-sdk
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

void playFire(AudioSink& sink, Pokey& pokey) {
    constexpr int steps = 128;

    for (int i = 0; i < steps; i++) {
        constexpr int duration = 120;
        constexpr uint8_t end_freq = 60;
        constexpr uint8_t start_freq = 5;
        constexpr uint8_t audc_val = 0x0F;

        // Sweep freq from start_freq to end_freq
        const uint8_t freq = start_freq + (end_freq - start_freq) * i / steps;
        pokey.poke(PokeyRegister::AUDF1, freq, 0);
        pokey.poke(PokeyRegister::AUDF1, freq, 0);
        pokey.poke(PokeyRegister::AUDC1, audc_val, 0);

        delay_ms(duration / steps);
        sink.writeAudio(pokey.renderAudio());
    }
    // Silence channel
    pokey.poke(PokeyRegister::AUDC1, 0x00, 0);
}

void playTone(Pokey& pokey, AudioSink& sink, const uint8_t audf, const uint8_t audc, const int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf, 1);
    pokey.poke(PokeyRegister::AUDC1, audc, 1);

    const uint64_t end = now_ms() + ms;
    while (now_ms() < end) {
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
    }
}

void playTones(AudioSink& sink, Pokey& pokey) {
    printf("tone 1\n");
    playTone(pokey, sink, 0x50, 0xA2, 400);  // lower tone

    // Soft tone 2
    printf("tone 2\n");
    playTone(pokey, sink, 0x30, 0xA4, 400);  // mid tone, slightly louder

    // Soft tone 3
    printf("tone 3\n");
    playTone(pokey, sink, 0x20, 0xA6, 400);  // higher tone

    // Silence
    pokey.poke(PokeyRegister::AUDC1, 0x00, 1);
    delay_ms(200);
}

void testAudioSinkA800(AudioSink& sink, Pokey& pokey) {
    printf("Running POKEY + AudioSink test...\n");
    sink.start();

    playTones(sink, pokey);
    playFire(sink, pokey);
    sink.stop();
    printf("Done.\n");
}