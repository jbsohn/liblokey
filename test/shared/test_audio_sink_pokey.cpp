#include <cstdio>
#ifdef PICO_ON_DEVICE
#include "pico/time.h"
#else
#include <chrono>
#include <thread>
#endif

#include "pokey/pokey.hpp"
#include "pokey/pokey_register.hpp"
#include "audio/audio_sink.hpp"
#include "test_audio_sink_pokey.hpp"

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
    printf("Playing fire...\n");
    constexpr int steps = 128;

    for (int i = 0; i < steps; i++) {
        constexpr int duration = 120;
        constexpr uint8_t end_freq = 60;
        constexpr uint8_t start_freq = 5;
        constexpr uint8_t audc_val = 0x0F;

        // Sweep freq from start_freq to end_freq
        const uint8_t freq = start_freq + (end_freq - start_freq) * i / steps;
        pokey.poke(PokeyRegister::AUDF1, freq);
        pokey.poke(PokeyRegister::AUDF1, freq);
        pokey.poke(PokeyRegister::AUDC1, audc_val);

        delay_ms(duration / steps);
        sink.writeAudio(pokey.renderAudio());
    }
    // Silence channel
    pokey.poke(PokeyRegister::AUDC1, 0x00);
    printf("done.\n");
}

void playTone(AudioSink& sink, Pokey& pokey, const uint8_t audf, const uint8_t audc, const int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf);
    pokey.poke(PokeyRegister::AUDC1, audc);

    const uint64_t end = now_ms() + ms;
    while (now_ms() < end) {
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
    }
}

void playTones(AudioSink& sink, Pokey& pokey) {
    printf("Starting tone test...\n");
    printf("tone 1\n");
    playTone(sink, pokey, 0x50, 0xA2, 1000);  // lower tone

    printf("tone 2\n");
    playTone(sink, pokey, 0x30, 0xA4, 1000);  // mid tone, slightly louder

    printf("tone 3\n");
    playTone(sink, pokey, 0x20, 0xA6, 1000);  // higher tone

    pokey.poke(PokeyRegister::AUDC1, 0x00);
    delay_ms(200);
    printf("done.\n");
}

void playGameOver(AudioSink& sink, Pokey& pokey) {
    printf("playing game over...\n");
    playTone(sink, pokey, 0x40, 0xA4, 200);
    playTone(sink, pokey, 0x38, 0xA4, 200);
    playTone(sink, pokey, 0x30, 0xA4, 200);
    playTone(sink, pokey, 0x28, 0xA4, 400);
    pokey.poke(PokeyRegister::AUDC1, 0x00);
    delay_ms(250);
    printf("done.\n");
}

void playLoop(AudioSink& sink, Pokey& pokey, const int loops = 12) {
    printf("playing loop %d times...\n", loops);

    for (int i = 0; i < loops; ++i) {
        constexpr int duration_ms = 180;
        constexpr uint8_t audc = 0xA4;
        constexpr uint8_t note2_freq = 0x28;
        constexpr uint8_t note1_freq = 0x38;
        playTone(sink, pokey, note1_freq, audc, duration_ms);
        playTone(sink, pokey, note2_freq, audc, duration_ms);
    }
    pokey.poke(PokeyRegister::AUDC1, 0x00);
    delay_ms(100);
    printf("done.\n");
}

void testAudioSinkPokey(AudioSink& sink, Pokey& pokey) {
    printf("Running POKEY + AudioSink test...\n");
    sink.start();

    playTones(sink, pokey);
    playFire(sink, pokey);
    playLoop(sink, pokey);
    playGameOver(sink, pokey);

    sink.stop();
    printf("Done.\n");
}