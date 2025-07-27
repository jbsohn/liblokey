#include <stdlib.h>
#include <stdio.h>
#include <fpm/fixed.hpp>
#include <cmath>
#include "atari.h"
#include "pokey_utils.hpp"

int Atari800_tv_mode = Atari800_TV_NTSC;

int PBI_IRQ = 0;
int PIA_IRQ = 0;
int CPU_IRQ = 0;
int ESC_enable_sio_patch = 0;

void* Util_malloc(const size_t size) {
    void* p = malloc(size);
    if (!p) {
        fprintf(stderr, "Util_malloc: Out of memory\n");
        exit(1);
    }
    return p;
}

void Log_print(const char* s) {
    fprintf(stderr, "LOG: %s\n", s);
}

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
