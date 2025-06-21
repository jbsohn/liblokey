#ifndef POKEY_ADAPTER_H_
#define POKEY_ADAPTER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct POKEY_instance POKEY_instance;

    void POKEY_init(POKEY_instance* p, float sample_rate);
    void POKEY_reset(POKEY_instance* p);
    void POKEY_poke(POKEY_instance* p, int address, uint8_t value);
    float POKEY_render_sample(POKEY_instance* p);

#ifdef __cplusplus
}
#endif

#endif
