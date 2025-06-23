// config.h - Stubbed configuration header for Atari800 integration
#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Fake any expected defines here

#define HAVE_STDINT_H 1

#ifndef LOKEY_ATARI_H
#define LOKEY_ATARI_H

#include <stdint.h>

typedef uint8_t  UBYTE;
typedef uint16_t UWORD;
typedef uint32_t ULONG;
typedef int32_t  SLONG;

#define TRUE  1
#define FALSE 0

// Missing globals
#define ANTIC_XPOS 0
#define ANTIC_LINE_C 1
int ESC_enable_sio_patch = 0;
int PBI_IRQ = 0;
int PIA_IRQ = 0;
int CPU_IRQ = 0;

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

// Fix warning: add parameter names to MZPOKEYSND_Init
static int MZPOKEYSND_Init(int snd_freq17, int playback_freq, int num_pokeys, int snd_flags, int quality) {
    return 0;
}

// Atari 800/XE/XL settings
extern int Atari800_tv_mode;  // 0 = NTSC, 1 = PAL (adjust if needed)
extern int Atari800_turbo = 0;
#define Atari800_TV_PAL 1
#define Atari800_FPS_NTSC 60
#define Atari800_FPS_PAL 50
#define ANTIC_CPU_CLOCK 1789772  // Roughly 1.79 MHz

// Utility functions
static void* Util_malloc(size_t size) { return malloc(size); }
static int Util_sscanbool(const char *ptr) { return strcmp(ptr, "0") == 0 ? 0 : 1; }
static int Util_sscandec(const char *ptr) { return atoi(ptr); }
static int Util_time(void) { return 0; }

// PLATFORM Sound
static int PLATFORM_SoundAvailable();
static int PLATFORM_SoundSetup(void *out) { return 1; }
static void PLATFORM_SoundPause(void) {}
static void PLATFORM_SoundExit(void) {}
static void PLATFORM_SoundContinue(void) {}
static void PLATFORM_SoundLock() {}
static void PLATFORM_SoundUnlock() {}
static void PLATFORM_SoundWrite(const void* buffer, unsigned int size) {}

// logging
static void Log_print(const char *format, ...) {}

#define Util_sleep(x) usleep((int)((x) * 1e6))  // sleep in microseconds

#endif // LOKEY_ATARI_H
#endif /* CONFIG_H */
