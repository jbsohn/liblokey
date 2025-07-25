#pragma once

#include <exception>
#include <tcb/span.hpp>
#include "pokey_register.hpp"

class Pokey {
public:
    virtual ~Pokey() = default;

    virtual void reset() = 0;
    virtual void poke(PokeyRegister address, uint8_t val, uint8_t gain) = 0;
    virtual tcb::span<const int16_t> renderAudio() = 0;

    [[nodiscard]] virtual const char* name() const {
        return "UnnamedPokey";
    }
};
