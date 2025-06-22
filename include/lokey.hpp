
#pragma once

#include "pokey_adapter.hpp"

class Lokey {
public:
    explicit Lokey(float sampleRate = 44100.0f, int numChannels = 1);

    void reset();
    void writeRegister(uint16_t address, uint8_t value) const;
    void render(float* outputBuffer, size_t frames);
private:
    PokeyAdapter adapter;
    int numChannels;
};