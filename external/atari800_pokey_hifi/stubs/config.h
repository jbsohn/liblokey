#pragma once

// This is a stubbed version of the config.h header from the Atari800 project.
// It exists to satisfy include dependencies in pokey.c but does not currently
// contain any functional declarations. Add contents here only if required.

#include <stdlib.h>
#include <stdint.h>

// NOTE: Atari800 expects SLONG to be 'int' on some platforms  but originally defined it as int32_t.
// This mismatch breaks on stricter toolchains like arm-none-eabi-gcc.
//
// On the Pico (PICO_ON_DEVICE), we use plain 'int' to keep compatibility and avoid signature or linkage issues.
// On the host, we prefer int32_t for portability and clarity.
#if defined(PICO_ON_DEVICE)
typedef int SLONG;
#else
typedef int32_t SLONG;
#endif

typedef uint32_t ULONG;
typedef int16_t SWORD;
typedef uint16_t UWORD;
typedef uint8_t UBYTE;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
