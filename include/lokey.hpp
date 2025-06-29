
#pragma once

#include "pokey_register.hpp"

class Lokey {
public:
    explicit Lokey(float sampleRate = 44100.0f, int numChannels = 1);
    void reset();
    void render(float* outputBuffer, const size_t frames);
};
