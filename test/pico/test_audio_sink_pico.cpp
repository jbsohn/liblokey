#include <array>
#include <memory>
#include "pico/stdlib.h"
#include "audio_sink.hpp"
#include "pico_audio_sink.hpp"

constexpr int sampleRate = 44100;
constexpr int bufferSize = 512;

std::array<int16_t, bufferSize> generateSquareWave(int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i)
        buf[i] = ((i / 32) % 2) ? amplitude : -amplitude;
    return buf;
}

[[noreturn]] int main() {
    stdio_init_all();
    std::unique_ptr<PicoAudioSink> sink = std::make_unique<PicoAudioSink>(0, sampleRate);
    sink->start();

    auto wave = generateSquareWave();
    while (true) {
        // Wait until there is enough space in the queue
        while (sink->getQueueLevel() > sink->getBufferSize() - bufferSize) {
            // sleep_ms(1);
        }
        sink->writeAudio(wave);
    }
}