#pragma once

#include "fpm/math.hpp"

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

using PFixed = fpm::fixed_16_16;

inline PFixed to_pfixed(const float f) {
    return static_cast<PFixed>(f);
}

inline float to_float(const PFixed f) {
    return static_cast<float>(f);
}

inline int to_int_trunc(const PFixed value) {
    return static_cast<int>(value);
}

inline int to_int_round(const PFixed value) {
    return static_cast<int>(fpm::round(value));
}

inline PFixed cos_fixed(const PFixed angle) {
    return static_cast<PFixed>(std::cosf(to_float(angle)));
}

inline PFixed get_fraction(const PFixed value, PFixed* int_part = nullptr) {
    const PFixed ipart = fpm::floor(value);
    if (int_part) {
        *int_part = ipart;  // write value to caller's pointer
    }
    return value - ipart;  // return the fractional part
}