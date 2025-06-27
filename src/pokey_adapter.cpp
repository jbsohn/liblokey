#include <stdio.h>
extern "C" {
}
#include "pokey_adapter.hpp"

PokeyAdapter::PokeyAdapter(const float sampleRate) {
    (void)sampleRate; // TODO: implement usage
    reset();
}

void PokeyAdapter::reset() {
}

void PokeyAdapter::poke(const PokeyRegister address, const uint8_t value) {
    (void)address; // TODO: implement usage
    (void)value; // TODO: implement usage
}

float PokeyAdapter::render() {
    return 0.0f;
}

