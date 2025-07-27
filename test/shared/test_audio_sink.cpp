
#include "test_audio_sink.hpp"

#include <cstdint>
#include <cstdio>

std::array<int16_t, bufferSize> generateSquareWave(int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i)
        buf[i] = i / 32 % 2 ? amplitude : -amplitude;
    return buf;
}

void test_audio_sink(AudioSink& sink) {
    printf("Starting direct audio sink test...\n");
    sink.start();

    auto wave = generateSquareWave();
    constexpr int totalSamples = sampleRate * 5;
    constexpr int numBuffers = totalSamples / bufferSize;

    for (int i = 0; i < numBuffers; ++i) {
        sink.writeAudio(wave);
    }

    sink.stop();
}
