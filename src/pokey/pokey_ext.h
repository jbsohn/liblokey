#pragma once

// extensions to pokey.c will go here to reduce changes with the Atari 800 version

#ifdef __cplusplus
extern "C" {
#endif
    // this will eventually hold the global variables in pokey.c
    typedef struct {
        uint8_t unused;
    } POKEY;

    float pokey_generate_sample();
#ifdef __cplusplus
}
#endif