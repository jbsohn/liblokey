#pragma once

#include <array>
#include <span>
#include "pokey/pokey.hpp"
#include "pokey/pokey_register.hpp"

class NullPokey final : public Pokey {
public:
    static constexpr size_t kFrameSize = 128;

private:
    std::array<int16_t, kFrameSize> buffer;

public:
    NullPokey() {
        buffer.fill(0);
    }
    ~NullPokey() noexcept override = default;

    void reset() override {}

    void poke(PokeyRegister address, const uint8_t val, const uint8_t gain) override {
        // Discard all writes
        (void)address;
        (void)val;
        (void)gain;
    }

    tcb::span<const int16_t> renderAudio() override {
        return buffer;
    }

    const char* name() const override {
        return "NullPokey";
    }
};
