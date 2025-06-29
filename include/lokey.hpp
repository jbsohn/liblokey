#pragma once

#include <memory>
#include "pokey.hpp"
#include "audio_sink.hpp"
#include "pokey_register.hpp"

class Lokey {
public:
    explicit Lokey(float sampleRate = 44100.0f, size_t bufferSize = 512);
    ~Lokey();

    void start();
    void reset();
    void poke(PokeyRegister reg, uint8_t val, uint8_t gain = 1);
    void renderAndPlay();

private:
    std::unique_ptr<Pokey> pokey;
    std::unique_ptr<AudioSink> sink;
    float sampleRate;
    size_t bufferSize;
};