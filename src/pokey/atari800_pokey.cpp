#include <cstdio>
#include <algorithm>
#include "atari800_pokey/pokeysnd.h"
#include "pokey/atari800_pokey.hpp"
#include "pokey/pokey_register.hpp"

Atari800Pokey::Atari800Pokey(const int sampleRate, const size_t bufferSize, const int channel)
    : sampleRate(sampleRate), bufferSize(bufferSize), channel(channel) {
    Atari800Pokey::reset();
}

Atari800Pokey::~Atari800Pokey() {
    printf("Atari800Pokey shutting down.\n");
}

void Atari800Pokey::reset() {
    POKEYSND_enable_new_pokey = TRUE;
    POKEYSND_bienias_fix = TRUE;
    audioBuffer.resize(bufferSize);
    POKEYSND_Init(POKEYSND_FREQ_17_APPROX, sampleRate, 2, POKEYSND_BIT16);
    POKEYSND_SetVolume(1);
}

void Atari800Pokey::poke(const PokeyRegister address, const uint8_t val) {
    POKEYSND_Update(addr(address), val, channel, 1);
}

std::span<const int16_t> Atari800Pokey::renderAudio() {
    POKEYSND_Process(audioBuffer.data(), static_cast<int>(bufferSize));

    for (size_t i = 0; i < bufferSize; ++i) {
        constexpr float POKEY_FIXED_GAIN = 16.0f;
        const float scaled = static_cast<float>(audioBuffer[i]) * POKEY_FIXED_GAIN;
        audioBuffer[i] = static_cast<int16_t>(std::clamp(static_cast<int>(scaled), -32767, 32767));
    }

    return {audioBuffer.data(), bufferSize};
}
