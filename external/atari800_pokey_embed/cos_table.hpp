
#pragma once

#include <fpm/fixed.hpp>
#include <array>

constexpr int COS_TABLE_SIZE = 256;
extern const std::array<fpm::fixed_16_16, COS_TABLE_SIZE> cos_table;

inline fpm::fixed_16_16 make_fixed_safe(const int val) {
    return fpm::fixed_16_16(static_cast<int64_t>(val) << 16);
}