#pragma once

#include <fpm/fixed.hpp>
#include <array>

// Initialize the POKEY emulator with the given sample rate.
void mzpokeysnd_ext_init(int sample_rate);

// Write a value to a POKEY register.
void mzpokeysnd_ext_write(int addr, int value);

// Render audio samples into the given buffer.
// `buffer` must be `count` samples long (16-bit signed PCM).
void mzpokeysnd_ext_render(int16_t* buffer, int count);

constexpr int COS_TABLE_SIZE = 256;
extern const std::array<fpm::fixed_16_16, COS_TABLE_SIZE> cos_table;

inline fpm::fixed_16_16 make_fixed_safe(const int val) {
    return fpm::fixed_16_16(static_cast<int64_t>(val) << 16);
}
