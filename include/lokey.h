#ifndef LOKEY_H_
#define LOKEY_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Initializes the audio engine with sample rate and channel count
    void lokey_init(float sample_rate, int num_channels);

    // Resets the internal PoKEY instance
    void lokey_reset(void);

    // Writes to a PoKEY register (addr should be 0x00–0x0F)
    void lokey_write_register(uint16_t address, uint8_t value);

    // Renders N frames of mono audio into output_buffer
    void lokey_render_audio(float* output_buffer, size_t frames);

#ifdef __cplusplus
}
#endif

#endif  // LOKEY_H_

