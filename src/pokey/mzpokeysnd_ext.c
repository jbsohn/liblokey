#include <stdlib.h>
#include <stdio.h>
#include "atari.h"

int POKEYSND_playback_freq = 44100;
int POKEYSND_volume = 192;
int Atari800_tv_mode = Atari800_TV_NTSC;

void (*POKEYSND_GenerateSync)(unsigned int) = NULL;

UBYTE POKEYSND_process_buffer[4096];  // Temporary stub buffer
int POKEYSND_process_buffer_fill = 0; // Stubbed fill level
int POKEYSND_process_buffer_length = 4096;
int POKEYSND_snd_flags = 0;

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
