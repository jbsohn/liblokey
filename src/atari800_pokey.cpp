// #include <fmt/format.h>
#include "atari800_pokey.hpp"
#include "atari800_pokey_embed/pokeysnd.hpp"
#include "pokey_register.hpp"

Atari800Pokey::Atari800Pokey(const int sampleRate, const size_t bufferSize, const int channel)
    : sampleRate(sampleRate), bufferSize(bufferSize), channel(channel) {
    Atari800Pokey::reset();
}

Atari800Pokey::~Atari800Pokey() {
    // fmt::print(stderr, "Atari800Pokey shutting down.\n");
}

void Atari800Pokey::reset() {
    POKEYSND_enable_new_pokey = FALSE;
    POKEYSND_bienias_fix = FALSE;
    audioBuffer.resize(bufferSize);
    POKEYSND_Init(POKEYSND_FREQ_17_APPROX, sampleRate, 2, POKEYSND_BIT8);
    POKEYSND_SetVolume(1.0f);
}

void Atari800Pokey::poke(PokeyRegister address, uint8_t val, uint8_t gain) {
    POKEYSND_Update(addr(address), val, channel, gain);
}

tcb::span<const int16_t> Atari800Pokey::renderAudio() {
    POKEYSND_Process(audioBuffer.data(), static_cast<int>(bufferSize));
    return {audioBuffer.data(), bufferSize};
}
