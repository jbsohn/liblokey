#include <thread>
#include "atari800_pokey.hpp"
#include "pico_audio_sink.hpp"

void playTone(Pokey& pokey, AudioSink& sink, uint8_t audf, uint8_t audc, int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf, 1);
    pokey.poke(PokeyRegister::AUDC1, audc, 1);

    const auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(ms);
    while (std::chrono::steady_clock::now() < end) {
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
        sleep_ms(4);
    }
}

[[noreturn]] int main() {
    const auto sink = std::make_unique<PicoAudioSink>(0, 22000, 2048);
    const auto pokey = std::make_unique<Atari800Pokey>(22000, 2048, 0);

    sink->start();

    while (true) {
        // Soft tone 1
        pokey->poke(PokeyRegister::AUDCTL, 0x00, 1);
        pokey->poke(PokeyRegister::AUDC1, 0xA2, 1);
        playTone(*pokey, *sink, 0x50, 0xA2, 800);  // lower tone

        // Soft tone 2
        playTone(*pokey, *sink, 0x30, 0xA4, 800);  // mid tone, slightly louder

        // Soft tone 3
        playTone(*pokey, *sink, 0x20, 0xA6, 800);  // higher tone

        // Silence
        pokey->poke(PokeyRegister::AUDC1, 0x00, 1);
        sleep_ms(500);
    }
}
