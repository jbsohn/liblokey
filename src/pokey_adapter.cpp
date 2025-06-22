
extern "C" {
#include "pokey/pokey.h"
#include "pokey/pokey_ext.h"
}
#include "pokey_adapter.hpp"

PokeyAdapter::PokeyAdapter(const float sampleRate) : sampleRate(sampleRate) {
    // TODO: initialise pokey instance
}

void PokeyAdapter::reset() {
    // TODO: reset pokey instance
}

void PokeyAdapter::poke(const PokeyRegister address, const uint8_t value) {
    POKEY_PutByte(static_cast<uint8_t>(address), value);
}

float PokeyAdapter::render() {
    return pokey_generate_sample();  // uses our hand-rolled audio engine
}
