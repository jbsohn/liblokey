#include <stdint.h>
#include "pokey.h"

// extensions to pokey.c will go here to reduce changes with the Atari 800 version

int CPU_IRQ = 0;
int PBI_IRQ = 0;
int PIA_IRQ = 0;
int ESC_enable_sio_patch = 0;
