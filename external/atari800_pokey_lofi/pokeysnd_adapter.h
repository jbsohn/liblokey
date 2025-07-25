#pragma once

#include "stubs.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int POKEYSND_Init(ULONG freq17,
                  int playback_freq,
                  UBYTE num_pokeys,
                  int flags);
void POKEYSND_SetVolume(int vol);
void POKEYSND_Update(UWORD addr, UBYTE val, UBYTE chip, UBYTE gain);
void POKEYSND_Process(void* sndbuffer, int sndn);

#ifdef __cplusplus
}
#endif