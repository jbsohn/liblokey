
#include "fpm/fixed.hpp"

#include <cmath>
#include "cos_table.hpp"

constexpr fpm::fixed_16_16 compute_cos_entry(int i) {
    constexpr float TWO_PI = 2.0f * static_cast<float>(M_PI);
    const float phase = static_cast<float>(i) / static_cast<float>(COS_TABLE_SIZE);
    return fpm::fixed_16_16(std::cosf(TWO_PI * phase));
}

constexpr std::array<fpm::fixed_16_16, COS_TABLE_SIZE> generate_cos_table() {
    std::array<fpm::fixed_16_16, COS_TABLE_SIZE> table;
    for (int i = 0; i < COS_TABLE_SIZE; ++i) {
        table[i] = compute_cos_entry(i);
    }
    return table;
}

const std::array<fpm::fixed_16_16, COS_TABLE_SIZE> cos_table = generate_cos_table();
