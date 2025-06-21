#include <string.h>
#include "pokey.h"
#include "pokey_adapter.h"

UBYTE lokey_sample_out = 127;

typedef struct {
    uint8_t unused; // placeholder for now
} POKEY;

struct POKEY_instance {
    POKEY pokey;
    float sample_rate;
};

void POKEY_init(POKEY_instance* p, float sample_rate) {
    p->sample_rate = sample_rate;

    // When we eventually use a real struct for POKEY,
    // this will zero/init the internal state.
    memset(&p->pokey, 0, sizeof(POKEY));
}

void POKEY_reset(POKEY_instance* p) {
    memset(&p->pokey, 0, sizeof(POKEY));
}

void POKEY_poke(POKEY_instance* p, int address, uint8_t value) {
    if (p != NULL)
    {
        POKEY_PutByte(address, value);
    }
}

float POKEY_render_sample(POKEY_instance* p) {
    if (p == NULL) { return 0.0f; }
    return (float)lokey_sample_out / 127.5f - 1.0f;
}
