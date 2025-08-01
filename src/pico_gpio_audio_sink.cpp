// pico_audio_sink.cpp
#include "pico_gpio_audio_sink.hpp"

#include <cstdio>

PicoGpioAudioSink::PicoGpioAudioSink(uint gpio, uint sampleRate, uint bufferSize) {}

PicoGpioAudioSink::~PicoGpioAudioSink() {
    queue_free(&sampleQueue);
}

void PicoGpioAudioSink::start() {
    if (running.exchange(true)) {
        return;
    }
    multicore_launch_core1(core1Task);
    multicore_fifo_push_blocking(reinterpret_cast<uint32_t>(this));
}

void PicoGpioAudioSink::stop() {
    if (!running.exchange(false)) {
        return;  // Not running
    }

    int16_t* buffer;
    while (queue_try_remove(&sampleQueue, &buffer)) {
        delete[] buffer;
    }
}

void PicoGpioAudioSink::writeAudio(std::span<const int16_t> samples) {}

void PicoGpioAudioSink::core1Task() {
    if (const auto ptr = reinterpret_cast<PicoGpioAudioSink*>(multicore_fifo_pop_blocking()); ptr != nullptr) {
        printf("TEST");
        ptr->playbackLoop();
    }
}

void PicoGpioAudioSink::playbackLoop() const {
    while (running.load()) {
    }
}
