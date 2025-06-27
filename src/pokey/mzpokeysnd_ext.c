#include <stdlib.h>
#include <stdio.h>
#include "atari.h"

int Atari800_tv_mode = Atari800_TV_NTSC;

void *Util_malloc(size_t size) {
    void *p = malloc(size);
    if (!p) {
        fprintf(stderr, "Util_malloc: Out of memory\n");
        exit(1);
    }
    return p;
}

void Log_print(const char *s) {
    fprintf(stderr, "LOG: %s\n", s);
}
