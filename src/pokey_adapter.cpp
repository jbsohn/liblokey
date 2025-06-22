
extern "C" {
#include "pokey/pokey.h"
}

#include "pokey_adapter.hpp"

PokeyAdapter::PokeyAdapter(const float sampleRate) : sampleRate(sampleRate) {
    // TODO: initialise pokey instance
}

void PokeyAdapter::reset() {
    // TODO: reset pokey instance
}

void PokeyAdapter::poke(const PokeyRegister address, const uint8_t value) const {
    POKEY_PutByte(static_cast<uint8_t>(address), value);
}

float PokeyAdapter::render() {
    static int phase = 0;
    phase++;
    return phase / 100 % 2 ? 1.0f : -1.0f;  // basic square wave
}
