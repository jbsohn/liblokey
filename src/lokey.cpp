#include "lokey.hpp"
#include "atari800_pokey.hpp"
#include "sdl_audio_sink.hpp"

Lokey::Lokey(float sampleRate, size_t bufferSize)
    : sampleRate(sampleRate), bufferSize(bufferSize) {
    pokey = std::make_unique<Atari800Pokey>(sampleRate, bufferSize, 0);
    sink = std::make_unique<SDLAudioSink>(sampleRate, bufferSize);
}

Lokey::~Lokey() {
}

void Lokey::start() {
    sink->start();
}

void Lokey::reset() {
    pokey->reset();
}

void Lokey::poke(PokeyRegister reg, uint8_t val, uint8_t gain) {
    pokey->poke(reg, val, gain);
}

void Lokey::renderAndPlay() {
    auto samples = pokey->renderAudio();
    sink->writeAudio(samples);
}