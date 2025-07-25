#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t UBYTE;
typedef uint16_t UWORD;
typedef int32_t SLONG;
typedef uint32_t ULONG;
typedef int16_t SWORD;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define POKEYSND_FREQ_17_EXACT     1789790	/* exact 1.79 MHz clock freq */
#define POKEYSND_FREQ_17_APPROX    1787520	/* approximate 1.79 MHz clock freq */


#define LINE_C 114
#define SEROUT_INTERVAL 31
#define XMTDONE_INTERVAL 31

#define POKEYSND_BIT16	1
#define POKEYSND_BIT8	2

// Forward-declared globals
extern int xpos;
extern int IRQ;
extern unsigned long cpu_clock;

// // Dummy IRQ function
static inline void GenerateIRQ(void) {
}

//
// // Dummy sound writer interface
// static inline int IsSoundFileOpen(void) {
//     return 0;
// }
//
// static inline void WriteToSoundFile(const unsigned char* data, int len) {
//     (void)data;
//     (void)len;
// }
//
// // State save/load stub implementations
// static inline void SaveUBYTE(UBYTE* data, int len) {
//     (void)data;
//     (void)len;
// }
//
// static inline void SaveINT(int* data, int len) {
//     (void)data;
//     (void)len;
// }
//
// static inline void ReadUBYTE(UBYTE* data, int len) {
//     (void)data;
//     (void)len;
// }
//
// static inline void ReadINT(int* data, int len) {
//     (void)data;
//     (void)len;
// }

static inline void WriteToSoundFile(const unsigned char* data, int len) {
    (void)data; // static inline void GenerateIRQ(void) {
}

static inline int IsSoundFileOpen(void) {
    return 0;
}

// State save/load stub implementations
static inline void SaveUBYTE(UBYTE* data, int len) {
    (void)data;
    (void)len;
}

static inline void SaveINT(int* data, int len) {
    (void)data;
    (void)len;
}

static inline void ReadUBYTE(UBYTE* data, int len) {
    (void)data;
    (void)len;
}

static inline void ReadINT(int* data, int len) {
    (void)data;
    (void)len;
}

static void SIO_PutByte(int byte) {
}

static int SIO_GetByte(void) {
    return 0;
}


static void INPUT_Scanline(void) {
}


#ifdef __cplusplus
}
#endif