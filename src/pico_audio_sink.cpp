#include "pico_audio_sink.hpp"
#include "pico/stdlib.h"
#include <algorithm>

constexpr int NUM_AUDIO_BUFFERS = 3;
constexpr int SAMPLES_PER_BUFFER = 256;

PicoAudioSink::PicoAudioSink(const uint32_t sampleRate, const int gpioPin) : sampleRate(sampleRate), gpioPin(gpioPin) {}

PicoAudioSink::~PicoAudioSink() = default;

void PicoAudioSink::start() {}

void PicoAudioSink::stop() {}

void PicoAudioSink::writeAudio(const tcb::span<const int16_t> samples) {}
