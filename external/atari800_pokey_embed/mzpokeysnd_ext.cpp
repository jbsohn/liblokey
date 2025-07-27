#include <stdlib.h>
#include <stdio.h>
#include "atari.h"

int Atari800_tv_mode = Atari800_TV_NTSC;

int PBI_IRQ = 0;
int PIA_IRQ = 0;
int CPU_IRQ = 0;
int ESC_enable_sio_patch = 0;

// int ANTIC_CPU_CLOCK = 1000;

void* Util_malloc(const size_t size) {
    void* p = malloc(size);
    if (!p) {
        fprintf(stderr, "Util_malloc: Out of memory\n");
        exit(1);
    }
    return p;
}

void Log_print(const char* s) {
    fprintf(stderr, "LOG: %s\n", s);
}
