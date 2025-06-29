#include <array>
#include <fmt/core.h>
#include "audio_sink.hpp"
#include "sdl_audio_sink.hpp"

constexpr int sampleRate = 44100;
constexpr int bufferSize = 512;

// Crude square wave test tone generator
std::array<int16_t, bufferSize> generateSquareWave(int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i)
        buf[i] = ((i / 32) % 2) ? amplitude : -amplitude;
    return buf;
}

[[noreturn]] int main() {
    fmt::print("Starting direct audio sink test...\n");

    std::unique_ptr<AudioSink> sink = std::make_unique<SDLAudioSink>(sampleRate, bufferSize);
    sink->start();

    auto wave = generateSquareWave();
    while (true) {
        sink->writeAudio(wave);
    }
}