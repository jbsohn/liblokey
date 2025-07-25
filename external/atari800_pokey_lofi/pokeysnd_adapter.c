#include <stdint.h>
#include <stddef.h>
#include "pokeysnd.h"
#include "pokeysnd_adapter.h"
#include "stubs.h"

int POKEYSND_Init(ULONG freq17,
                  int playback_freq,
                  UBYTE num_pokeys,
                  int flags) {
    Pokey_sound_init(freq17, playback_freq, num_pokeys);
    return 1;
}

void POKEYSND_SetVolume(int vol) {
}

void POKEYSND_Update(UWORD addr, UBYTE val, UBYTE chip, UBYTE gain) {
    Update_pokey_sound(addr, val, chip, gain);
}

void POKEYSND_Process(void* sndbuffer, int sndn) {
    Pokey_process(sndbuffer, sndn);
}