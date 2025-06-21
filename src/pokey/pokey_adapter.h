#ifndef POKEY_ADAPTER_H_
#define POKEY_ADAPTER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    // this will eventually hold the global variables in pokey.c
    typedef struct {
        uint8_t unused; // placeholder for now
    } POKEY;

    typedef struct POKEY_instance {
        POKEY pokey;
        float sample_rate;
    } POKEY_instance;

    void POKEY_init(POKEY_instance* p, float sample_rate);
    void POKEY_reset(POKEY_instance* p);
    void POKEY_poke(POKEY_instance* p, int address, uint8_t value);
    float POKEY_render_sample(POKEY_instance* p);

#ifdef __cplusplus
}
#endif

#endif
