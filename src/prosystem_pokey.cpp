#include <cstdio>
#include <algorithm>
#include "prosystem_pokey.hpp"
#include "pokey_register.hpp"

extern "C" {
#include "prosystem_pokey/pokey.h"
}

ProSystemPokey::ProSystemPokey(const int sampleRate) : sampleRate(sampleRate) {
    ProSystemPokey::reset();
}

ProSystemPokey::~ProSystemPokey() {
    printf("ProSystemPokey shutting down.\n");
}

void ProSystemPokey::reset() {
    audioBuffer.resize(pokey_size);
    pokey_setSampleRate(sampleRate);
    pokey_Reset();
}

void ProSystemPokey::poke(const PokeyRegister address, const uint8_t val) {
    const uint16_t adr = addr(address) + 0x4000;
    pokey_SetRegister(adr, val);
}

std::span<const int16_t> ProSystemPokey::renderAudio() {
    pokey_Process(pokey_size);
    std::transform(pokey_buffer, pokey_buffer + pokey_size, audioBuffer.begin(),
                   [](const uint8_t s) { return static_cast<int16_t>((static_cast<int16_t>(s) - 128) << 8); });

    return {audioBuffer.data(), pokey_size};
}
