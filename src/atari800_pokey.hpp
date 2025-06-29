#pragma once

#include <tcb/span.hpp>
#include "pokey.hpp"

class atari800_pokey : public Pokey {
public:
    ~atari800_pokey() override;

    void reset() override;
    void poke(PokeyRegister address, uint8_t val, uint8_t gain) override;
    tcb::span<const int16_t> renderAudio() override;

    const char* name() const override { return "Atari800Pokey"; }
};
