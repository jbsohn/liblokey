#include <cstddef>
#include "lokey.hpp"

Lokey::Lokey(const float sampleRate, const int numChannels)
    : adapter(sampleRate), numChannels(numChannels) {
    adapter.reset();
}

void Lokey::reset()
{
    adapter.reset();
}

void Lokey::writeRegister(uint16_t address, uint8_t value) const {
    adapter.poke(address, value);
}

void Lokey::render(float* outputBuffer, size_t frames)
{
    for (size_t i = 0; i < frames; ++i) {
        const float sample = adapter.render();
        outputBuffer[i] = sample;  // Mono output for now
    }
}
