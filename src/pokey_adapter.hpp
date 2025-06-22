#pragma once

#include "pokey/pokey.h"
#include "pokey/pokey_ext.h"

class PokeyAdapter {
public:
    explicit PokeyAdapter(const float sampleRate);
    void reset();
    void poke(const uint16_t address, const uint8_t value) const;
    [[nodiscard]] float render();

private:
    const float sampleRate;
};