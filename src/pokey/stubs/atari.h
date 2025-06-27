// atari.h - Minimal header to support Atari800 POKEY code
#pragma once

// This is a stubbed version of the atari.h header from the Atari800 project.
// It exists to satisfy include dependencies in pokey.c but does not currently
// contain any functional declarations. Add contents here only if required.

#include "config.h"

#define Atari800_TV_NTSC 0
#define Atari800_TV_PAL 1
#define Atari800_FPS_NTSC 60
#define Atari800_FPS_PAL 50
#define Atari800_TV_PAL 1
#define Atari800_FPS_NTSC 60
#define Atari800_FPS_PAL 50
#define ANTIC_CPU_CLOCK 1789772  // Roughly 1.79 MHz

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

// Atari 800/XE/XL settings
extern int Atari800_tv_mode;  // 0 = NTSC, 1 = PAL (adjust if needed)
extern int Atari800_turbo;

// Missing globals
#define ANTIC_XPOS 0
#define ANTIC_LINE_C 1

extern int ESC_enable_sio_patch;
extern int PBI_IRQ;
extern int PIA_IRQ;
extern int CPU_IRQ;

// Missing functions
static int CASSETTE_IOLineStatus(void) { return 0; }
static void CPU_GenerateIRQ(void) {}
static void SIO_PutByte(int byte) {}
static int  SIO_GetByte(void) { return 0; }
static void CASSETTE_ResetPOKEY(void) {}
static int  CASSETTE_AddScanLine(void) { return 0; }
static int  INPUT_Playingback(void) { return 0; }
static int  INPUT_PlaybackInt(void) { return 0; }
static int  INPUT_Recording(void) { return 0; }
static void INPUT_RecordInt(int dummy) {}
static void INPUT_Scanline(void) {}
static void SndSave_CloseSoundFile(void) {}
static void SndSave_WriteToSoundFile(const unsigned char*, int) {}

// Needed for pokey.c
#define SIO_SEROUT_INTERVAL 0
#define SIO_XMTDONE_INTERVAL 0

// Needed for pokey.c save/load routines
#define STATESAV_TAG(x) #x
static void StateSav_SaveUBYTE(UBYTE* /*data*/, int /*len*/) {}
static void StateSav_SaveINT(int* /*data*/, int /*len*/) {}
static void StateSav_ReadUBYTE(UBYTE* /*data*/, int /*len*/) {}
static void StateSav_ReadINT(int* /*data*/, int /*len*/) {}
