#pragma once

#include <vector>
#include "pokey/pokey.hpp"

class ProSystemPokey final : public Pokey {
public:
    explicit ProSystemPokey(int sampleRate = 44100);
    ~ProSystemPokey() override;
    void reset() override;
    void poke(PokeyRegister address, uint8_t val) override;
    std::span<const int16_t> renderAudio() override;

    [[nodiscard]] const char* name() const override {
        return "ProSystemPokey";
    }

private:
    int sampleRate;
    std::vector<int16_t> audioBuffer;
};
