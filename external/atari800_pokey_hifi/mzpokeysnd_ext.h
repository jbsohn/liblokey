#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    // Initialize the POKEY emulator with the given sample rate.
    void mzpokeysnd_ext_init(int sample_rate);

    // Write a value to a POKEY register.
    void mzpokeysnd_ext_write(int addr, int value);

    // Render audio samples into the given buffer.
    // `buffer` must be `count` samples long (16-bit signed PCM).
    void mzpokeysnd_ext_render(int16_t* buffer, int count);

#ifdef __cplusplus
}
#endif