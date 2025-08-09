#pragma once

#include <cstdint>
#include <cstdio>
#include "pico/time.h"

class PicoTimeIt {
public:
    ~PicoTimeIt() {
        const absolute_time_t end = get_absolute_time();
        const std::int64_t elapsed_us = absolute_time_diff_us(start, end);
        const float elapsed_sec = elapsed_us / 1e6f;
        std::printf("Elapsed time: %f seconds\n", elapsed_sec);
    }

private:
    absolute_time_t start = get_absolute_time();
};