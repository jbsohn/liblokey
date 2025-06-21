#pragma once

extern "C" {
#include "lokey.h"
}

#include <vector>

namespace lokey {

class AudioEngine {
public:
    AudioEngine() {
        lokey_init();
    }

    void write(uint8_t addr, uint8_t value) {
        lokey_write_register(addr, value);
    }

    void render(float* buffer, int frames) {
        lokey_generate_audio(buffer, frames);
    }

    void render(std::vector<float>& buffer) {
        render(buffer.data(), static_cast<int>(buffer.size()));
    }
};

} // namespace lokey
