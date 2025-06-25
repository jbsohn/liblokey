#include <cstddef>
#include <cassert>
#include "lokey.hpp"


Lokey::Lokey(const float sampleRate, const int numChannels) : numChannels(numChannels) {
    assert(this->numChannels == 1 && "Only mono output is supported right now");
}

void Lokey::reset() {
}

void Lokey::poke(const PokeyRegister address, const uint8_t value) {
}

void Lokey::render(float* outputBuffer, const size_t frames) {

}
