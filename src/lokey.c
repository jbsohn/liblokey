#include "lokey.h"

#include <stdlib.h>

#include "pokey/pokey_adapter.h"

// Static internal state
static POKEY_instance *pokey;
static float sample_rate = 44100.0f;
static int num_channels = 1;

void lokey_init(float sr, int channels) {
    sample_rate = sr;
    num_channels = channels;

    if (!pokey) {
        pokey = (POKEY_instance*)malloc(sizeof(*pokey));
    }
    POKEY_init(pokey, sample_rate);

    // Initialize the PoKEY chip with the given sample rate
    POKEY_init(pokey, sample_rate);

    // Reset to clear any internal state
    POKEY_reset(pokey);
}

void lokey_reset(void) {
    POKEY_reset(pokey);
}

void lokey_write_register(uint16_t address, uint8_t value) {
    // Mask to valid register range (0x00–0x0F)
    POKEY_poke(pokey, address & 0x0F, value);
}

void lokey_render_audio(float* output_buffer, size_t frames) {
    if (!output_buffer) return;

    for (size_t i = 0; i < frames; ++i) {
        float sample = POKEY_render_sample(pokey);
        output_buffer[i] = sample;  // Mono output for now
    }
}
