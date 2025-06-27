#pragma once

// This is a stubbed version of the config.h header from the Atari800 project.
// It exists to satisfy include dependencies in pokey.c but does not currently
// contain any functional declarations. Add contents here only if required.

#include <stdlib.h>
#include <stdint.h>

typedef int32_t  SLONG;
typedef uint32_t ULONG;
typedef int16_t  SWORD;
typedef uint16_t UWORD;
typedef uint8_t  UBYTE;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

