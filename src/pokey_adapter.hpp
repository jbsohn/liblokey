#pragma once

#include "pokey_registers.hpp"

class PokeyAdapter {
public:
    explicit PokeyAdapter(const float sampleRate);
    void reset();
    void poke(const PokeyRegister address, const uint8_t value);
    [[nodiscard]] float render();

private:
    const float sampleRate;
};