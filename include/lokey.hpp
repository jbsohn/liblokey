
#pragma once

#include "pokey_register.hpp"

#define POKEYSND_FLAG_S16    0x01
#define POKEYSND_FLAG_MONO   0x02
#define POKEYSND_FLAG_STEREO 0x00  // default if MONO is not set

class Lokey {
public:
    static Lokey& instance();

    bool init(int sampleRate = 44100);
    void reset_registers();
    void poke(PokeyRegister address, uint8_t value);
    void render(int16_t* buffer, int samples);
};