#include <array>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <numbers>
#include "test_audio_sink.hpp"

// Generates a square wave at a given freq
std::array<int16_t, bufferSize> generateSquareWave(const float freq = 440.0f, const int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i) {
        const float t = static_cast<float>(i) / sampleRate;
        buf[i] = std::sin(2 * std::numbers::pi * freq * t) > 0 ? amplitude : -amplitude;
    }
    return buf;
}

// Generates a sine wave at a given freq
std::array<int16_t, bufferSize> generateSineWave(const float freq = 440.0f, const int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i) {
        const float t = static_cast<float>(i) / sampleRate;
        buf[i] = static_cast<int16_t>(std::sin(2 * std::numbers::pi * freq * t) * amplitude);
    }
    return buf;
}

// Frequency sweep (sine)
std::array<int16_t, bufferSize> generateSweepWave(float startFreq,
                                                  float endFreq,
                                                  int bufferIndex,
                                                  int totalBuffers,
                                                  int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i) {
        const float t = static_cast<float>(i + bufferIndex * bufferSize) / sampleRate;
        const float freq = startFreq + (endFreq - startFreq) * (t / 5.0f);  // 5s sweep
        buf[i] = static_cast<int16_t>(std::sin(2 * std::numbers::pi * freq * t) * amplitude);
    }
    return buf;
}

// White noise
std::array<int16_t, bufferSize> generateNoise(int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i) {
        buf[i] = rand() % (2 * amplitude) - amplitude;
    }
    return buf;
}

void testAudioSink(AudioSink& sink) {
    printf("Starting direct audio sink test...\n");
    sink.start();

    for (int i = 0; i < 20; i++) {
        sink.writeAudio(generateSquareWave(440.0f));
    }

    constexpr int sweepBuffers = 40;
    for (int i = 0; i < sweepBuffers; i++) {
        sink.writeAudio(generateSweepWave(220.0f, 880.0f, i, sweepBuffers));
    }

    for (constexpr float melodyFreqs[] = {440, 494, 523, 587, 659, 698, 784, 880}; const float noteFreq : melodyFreqs) {
        for (int i = 0; i < 8; i++) {
            sink.writeAudio(generateSineWave(noteFreq));
        }
    }

    for (int i = 0; i < 20; i++) {
        sink.writeAudio(generateNoise());
    }

    for (int i = 0; i < 12; i++) {
        sink.writeAudio(i % 2 == 0 ? generateSineWave(330.0f) : generateSquareWave(330.0f));
    }

    sink.stop();
}
