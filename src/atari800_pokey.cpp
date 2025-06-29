#include "atari800_pokey.hpp"
#include "pokey/pokeysnd.h"
#include "pokey_register.hpp"

Atari800Pokey::Atari800Pokey(const int sampleRate, const size_t bufferSize, const int channel):
    sampleRate(sampleRate), bufferSize(bufferSize), channel(channel)
{
    Atari800Pokey::reset();
}

Atari800Pokey::~Atari800Pokey() {

}

void Atari800Pokey::reset() {
    audioBuffer.resize(bufferSize);
    POKEYSND_Init(POKEYSND_FREQ_17_APPROX, sampleRate, 2, POKEYSND_BIT16);
}

void Atari800Pokey::poke(PokeyRegister address, uint8_t val, uint8_t gain) {
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, channel, 1);
}

tcb::span<const int16_t> Atari800Pokey::renderAudio() {
    POKEYSND_Process(audioBuffer.data(), static_cast<int>(bufferSize));
    return {audioBuffer.data(), bufferSize};
}
