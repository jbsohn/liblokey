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

void playTone(Pokey& pokey, AudioSink& sink, const uint8_t audf, const uint8_t audc, const int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf, 1);
    pokey.poke(PokeyRegister::AUDC1, audc, 1);

    const uint64_t end = now_ms() + ms;
    while (now_ms() < end) {
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
    }
}

void test_audio_sink_a800(AudioSink& sink, Pokey& pokey) {
    printf("Running POKEY + AudioSink test...\n");
    sink.start();

    printf("tone 1\n");
    playTone(pokey, sink, 0x50, 0xA2, 800);  // lower tone

    // Soft tone 2
    printf("tone 2\n");
    playTone(pokey, sink, 0x30, 0xA4, 800);  // mid tone, slightly louder

    // Soft tone 3
    printf("tone 3\n");
    playTone(pokey, sink, 0x20, 0xA6, 800);  // higher tone

    // Silence
    pokey.poke(PokeyRegister::AUDC1, 0x00, 1);
    delay_ms(800);

    sink.stop();
    printf("Done.\n");
}