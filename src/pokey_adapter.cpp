#include <stdio.h>
extern "C" {
#include "pokey/pokey.h"
}
#include "pokey_adapter.hpp"

PokeyAdapter::PokeyAdapter(const float sampleRate) : sampleRate(sampleRate) {
    reset();
}

void PokeyAdapter::reset() {
}

void PokeyAdapter::poke(const PokeyRegister address, const uint8_t value) {
    POKEY_PutByte(static_cast<uint8_t>(address), value);
}

float PokeyAdapter::render() {
}

