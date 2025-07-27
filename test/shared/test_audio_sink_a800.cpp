#include <thread>
#include <chrono>
#include <fmt/core.h>
#include "test_audio_sink_a800.hpp"

void playTone(Pokey& pokey, AudioSink& sink, uint8_t audf, uint8_t audc, int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf, 1);
    pokey.poke(PokeyRegister::AUDC1, audc, 1);

    const auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(ms);
    while (std::chrono::steady_clock::now() < end) {
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
    }
}

void test_audio_sink_a800(SDLAudioSink sink, Atari800Pokey pokey) {
    printf("Running Atari800 POKEY + SDL AudioSink test...\n");
    sink.start();

    // Soft tone 1
    pokey.poke(PokeyRegister::AUDCTL, 0x00, 1);
    pokey.poke(PokeyRegister::AUDC1, 0xA2, 1);
    playTone(pokey, sink, 0x50, 0xA2, 800);  // lower tone

    // Soft tone 2
    playTone(pokey, sink, 0x30, 0xA4, 800);  // mid tone, slightly louder

    // Soft tone 3
    playTone(pokey, sink, 0x20, 0xA6, 800);  // higher tone

    // Silence
    pokey.poke(PokeyRegister::AUDC1, 0x00, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    sink.stop();
    printf("Done.\n");
}