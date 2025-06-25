#include "lokey.hpp"
#include "pokey/pokeysnd.h"

#define POKEYSND_FLAG_S16  0x01
#define POKEYSND_FLAG_MONO 0x02

Lokey& Lokey::instance() {
    static Lokey singleton;
    return singleton;
}

bool Lokey::init(int sampleRate) {
#ifdef __PLUS
    int clear_regs = 1;
    return POKEYSND_Init(
        1789790,          // base frequency (NTSC POKEY clock)
        sampleRate,       // output sample rate
        1,                // number of POKEYs
        POKEYSND_FLAG_S16 | POKEYSND_FLAG_MONO,
        clear_regs
    ) == 0;
#else
    return POKEYSND_Init(
        1789790,
        sampleRate,
        1,
        POKEYSND_FLAG_S16 | POKEYSND_FLAG_MONO
    ) == 0;
#endif
}


void Lokey::reset_registers() {
    for (int i = 0; i < 16; ++i)
        poke(static_cast<PokeyRegister>(i), 0);
}

void Lokey::poke(const PokeyRegister address, const uint8_t value) {
    POKEYSND_Update(static_cast<uint16_t>(address), value, 0, 0); // chip 0, full gain
}

void Lokey::render(int16_t* buffer, int samples) {
    POKEYSND_Process(buffer, samples);
}