#pragma once

#include "pokey/pokey.h"
#include "pokey_registers.hpp"

class PokeyAdapter {
public:
    explicit PokeyAdapter(const float sampleRate);
    void reset();
    void poke(const PokeyRegister address, const uint8_t value) const;
    [[nodiscard]] float render();

private:
    const float sampleRate;
};