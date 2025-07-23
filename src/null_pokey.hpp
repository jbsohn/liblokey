#pragma once

#include "pokey.hpp"
#include "pokey_register.hpp"

#include <array>

class NullPokey final : public Pokey {
public:
    static constexpr size_t kFrameSize = 128;

    NullPokey() {
        buffer.fill(0);
    }

    void reset() override {}

    void poke(PokeyRegister address, const uint8_t val, const uint8_t gain) override {
        // Discard all writes
        (void)address;
        (void)val;
        (void)gain;
    }

    tcb::span<const int16_t> renderAudio() override {
        // Return silence
        return buffer;
    }

    const char* name() const override {
        return "NullPokey";
    }

private:
    std::array<int16_t, kFrameSize> buffer;
};
