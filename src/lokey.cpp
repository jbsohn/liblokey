#include "lokey.hpp"
#include "atari800_pokey.hpp"

#ifdef PICO_ON_DEVICE
#include "pico_audio_sink.hpp"
#else
#include "sdl_audio_sink.hpp"
#endif

Lokey::Lokey(float sampleRate, size_t bufferSize) : sampleRate(sampleRate), bufferSize(bufferSize) {
    pokey = std::make_unique<Atari800Pokey>(sampleRate, bufferSize, 0);

#ifdef PICO_ON_DEVICE
    sink = std::make_unique<PicoAudioSink>(sampleRate, 1);
#else
    sink = std::make_unique<SDLAudioSink>(sampleRate, bufferSize);
#endif
}

Lokey::~Lokey() = default;

void Lokey::start() const {
    sink->start();
}

void Lokey::reset() const {
    pokey->reset();
}

void Lokey::poke(const PokeyRegister reg, const uint8_t val, const uint8_t gain) const {
    pokey->poke(reg, val, gain);
}

void Lokey::renderAndPlay() const {
    const auto samples = pokey->renderAudio();
    sink->writeAudio(samples);
}