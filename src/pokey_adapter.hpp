#pragma once

#include "pokey_register.hpp"

class PokeyAdapter {
public:
    explicit PokeyAdapter(const float sampleRate);
    void reset();
    void poke(const PokeyRegister address, const uint8_t value);
    [[nodiscard]] float render();
};