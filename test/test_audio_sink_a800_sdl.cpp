#include <thread>
#include <fmt/format.h>
#include "atari800_pokey.hpp"
#include "sdl_audio_sink.hpp"

int main() {
    std::unique_ptr<Pokey> pokey = std::make_unique<Atari800Pokey>(44100, 512, 0);
    std::unique_ptr<AudioSink> sink = std::make_unique<SDLAudioSink>();

    pokey->poke(PokeyRegister::AUDCTL, 0x00, /*gain=*/1);
    pokey->poke(PokeyRegister::AUDF1, 0x28, 1);
    pokey->poke(PokeyRegister::AUDC1, 0xA0, 1);

    sink->start();

    fmt::print("starting loop...\n");

    // Then in a loop:
    while (true) {
        auto samples = pokey->renderAudio();
        sink->writeAudio(samples);
    }
}
