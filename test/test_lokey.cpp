#include <SDL.h>
#include <thread>
#include <chrono>
#include <vector>
#include <fmt/core.h>
#include "lokey.hpp"

// A short musical phrase using POKEY
struct Note {
    uint8_t freq;
    uint8_t control;
    int duration_ms;
};

void playNote(Lokey& lokey, const Note& note) {
    lokey.poke(PokeyRegister::AUDF1, note.freq);
    lokey.poke(PokeyRegister::AUDC1, note.control);

    auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(note.duration_ms);
    while (std::chrono::steady_clock::now() < end) {
        lokey.renderAndPlay();
        SDL_Delay(4);
    }
}

int main() {
    fmt::print("Playing a short tune with Lokey...\n");

    Lokey lokey;
    lokey.start();
    lokey.poke(PokeyRegister::AUDCTL, 0x00); // normal mode

    std::vector<Note> tune = {
        {0x30, 0xA4, 200},
        {0x28, 0xA4, 200},
        {0x24, 0xA4, 200},
        {0x20, 0xA4, 300},
        {0x24, 0xA4, 150},
        {0x28, 0xA4, 150},
        {0x30, 0xA4, 300},
        {0x00, 0x00, 200}, // rest
    };

    for (const auto& note : tune) {
        playNote(lokey, note);
    }

    fmt::print("Done.\n");
    return 0;
}