
#pragma once

#include "pokey_adapter.hpp"
#include "pokey_register.hpp"

class Lokey {
public:
    explicit Lokey(float sampleRate = 44100.0f, int numChannels = 1);

    void reset();
    void poke(const PokeyRegister address, const uint8_t value);
    void render(float* outputBuffer, const size_t frames);

private:
    PokeyAdapter adapter;
    int numChannels;
};
