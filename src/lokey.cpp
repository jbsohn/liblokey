#include <cstddef>
#include <cassert>
#include "lokey.hpp"

Lokey::Lokey(const float sampleRate, const int numChannels) : adapter(sampleRate), numChannels(numChannels) {
    assert(this->numChannels == 1 && "Only mono output is supported right now");
    adapter.reset();
}

void Lokey::reset() {
    adapter.reset();
}

void Lokey::poke(const PokeyRegister address, const uint8_t value) {
    adapter.poke(address, value);
}

void Lokey::render(float* outputBuffer, const size_t frames) {
    for (size_t i = 0; i < frames; ++i) {
        const float sample = adapter.render();
        outputBuffer[i] = sample; // Mono output for now
    }
}
