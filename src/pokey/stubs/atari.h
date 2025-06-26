// atari.h - Minimal header to support Atari800 POKEY code
#pragma once

// This is a stubbed version of the atari.h header from the Atari800 project.
// It exists to satisfy include dependencies in pokey.c but does not currently
// contain any functional declarations. Add contents here only if required.

#include <stdint.h>
#include <stddef.h>

typedef uint8_t  UBYTE;
typedef uint16_t UWORD;
typedef uint32_t ULONG;
typedef int16_t  SWORD;


extern int POKEYSND_playback_freq;
extern int POKEYSND_volume;

#define Atari800_TV_NTSC 0
#define Atari800_TV_PAL 1

#define Atari800_FPS_NTSC 60
#define Atari800_FPS_PAL 50

extern int Atari800_tv_mode;

void *POKEYSND_Update_ptr;
void *POKEYSND_Process_ptr;

#define POKEY_OFFSET_AUDF1 0x00
#define POKEY_OFFSET_AUDC1 0x01
#define POKEY_OFFSET_AUDF2 0x02
#define POKEY_OFFSET_AUDC2 0x03
#define POKEY_OFFSET_AUDF3 0x04
#define POKEY_OFFSET_AUDC3 0x05
#define POKEY_OFFSET_AUDF4 0x06
#define POKEY_OFFSET_AUDC4 0x07
#define POKEY_OFFSET_AUDCTL 0x08
#define POKEY_OFFSET_STIMER 0x09
#define POKEY_OFFSET_SKRES 0x0a
#define POKEY_OFFSET_POTGO 0x0b
#define POKEY_OFFSET_SEROUT 0x0d
#define POKEY_OFFSET_IRQEN 0x0e
#define POKEY_OFFSET_SKCTL 0x0f

#define POKEY_OFFSET_POT0 0x00
#define POKEY_OFFSET_POT1 0x01
#define POKEY_OFFSET_POT2 0x02
#define POKEY_OFFSET_POT3 0x03
#define POKEY_OFFSET_POT4 0x04
#define POKEY_OFFSET_POT5 0x05
#define POKEY_OFFSET_POT6 0x06
#define POKEY_OFFSET_POT7 0x07
#define POKEY_OFFSET_ALLPOT 0x08
#define POKEY_OFFSET_KBCODE 0x09
#define POKEY_OFFSET_RANDOM 0x0a
#define POKEY_OFFSET_SERIN 0x0d
#define POKEY_OFFSET_IRQST 0x0e
#define POKEY_OFFSET_SKSTAT 0x0f

#define POKEYSND_BIT16	1

extern void (*POKEYSND_GenerateSync)(unsigned int);

extern UBYTE POKEYSND_process_buffer[4096];
extern int POKEYSND_process_buffer_fill;

extern int POKEYSND_process_buffer_length;

extern int POKEYSND_snd_flags;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
