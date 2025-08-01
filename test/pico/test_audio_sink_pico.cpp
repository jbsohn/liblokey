#include <array>
#include <memory>
#include "pico/stdlib.h"
#include "audio_sink.hpp"
#include "pico_gpio_audio_sink.hpp"
#include "pico/bootrom.h"

constexpr int sampleRate = 22050;
constexpr int bufferSize = 512;

std::array<int16_t, bufferSize> generateSquareWave(int16_t amplitude = 3000) {
    std::array<int16_t, bufferSize> buf{};
    for (int i = 0; i < bufferSize; ++i)
        buf[i] = (i / 32) % 2 ? amplitude : -amplitude;
    return buf;
}

int main() {
    stdio_init_all();
    PicoGpioAudioSink sink(0, sampleRate);
    sink.start();

    auto wave = generateSquareWave();
    while (true) {
        // Wait until there is enough space in the queue
        while (sink.getQueueLevel() > sink.getBufferSize() - bufferSize) {
            sleep_ms(1);
        }
        sink.writeAudio(wave);
    }
}