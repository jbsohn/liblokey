#pragma once

#include <vector>
#include "pokey.hpp"

class Atari800Pokey final : public Pokey {
public:
    explicit Atari800Pokey(int sampleRate = 44100, size_t bufferSize = 512, int channel = 0);
    ~Atari800Pokey() override;

    void reset() override;
    void poke(PokeyRegister address, uint8_t val, uint8_t gain) override;
    std::span<const int16_t> renderAudio() override;

    [[nodiscard]] const char* name() const override { return "Atari800Pokey"; }
private:
    int sampleRate;
    size_t bufferSize;
    int channel;
    std::vector<int16_t> audioBuffer;
};
