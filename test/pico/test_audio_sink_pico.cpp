#include <array>
#include <memory>
#include <cmath>
#include "pico/stdlib.h"
#include "pico_gpio_audio_sink.hpp"
#include "pico/bootrom.h"

constexpr int sampleRate = 22050;
constexpr int bufferSize = 512;

std::array<int16_t, bufferSize> generateSquareWave(const float freq, const int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    const float samplesPerCycle = sampleRate / freq;
    for (int i = 0; i < bufferSize; ++i) {
        buf[i] = fmod(i, samplesPerCycle) < (samplesPerCycle / 2) ? amplitude : -amplitude;
    }
    return buf;
}

int main() {
    stdio_init_all();
    PicoGpioAudioSink sink(0, sampleRate);
    sink.start();

    float freq = 220.0f;
    float freqStep = 1.01f;  // Adjust to taste
    int count = 0;

    while (count < 2) {
        auto wave = generateSquareWave(freq);
        sink.writeAudio(wave);
        freq *= freqStep;
        if (freq > 1200.0f) {
            freq = 220.0f;
            count++;
        }
    }

    reset_usb_boot(0, 0);
}
