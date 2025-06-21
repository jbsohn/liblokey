#include <string.h>
#include "pokey.h"
#include "pokey_adapter.h"

static UBYTE lokey_sample_out = 127;

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
    static int phase = 0;
    phase++;
    return (float)((phase / 100) % 2 ? 1.0f : -1.0f);  // basic square wave
}
