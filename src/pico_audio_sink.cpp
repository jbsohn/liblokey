// pico_audio_sink.cpp
#include "pico_audio_sink.hpp"

#include <cstdio>

PicoAudioSink::PicoAudioSink(uint gpio, uint sampleRate, uint bufferSize) {}

PicoAudioSink::~PicoAudioSink() {
    queue_free(&sampleQueue);
}

void PicoAudioSink::start() {
    if (running.exchange(true)) {
        return;
    }
    multicore_launch_core1(core1Task);
    multicore_fifo_push_blocking(reinterpret_cast<uint32_t>(this));
}

void PicoAudioSink::stop() {
    if (!running.exchange(false)) {
        return;  // Not running
    }

    int16_t* buffer;
    while (queue_try_remove(&sampleQueue, &buffer)) {
        delete[] buffer;
    }
}

void PicoAudioSink::writeAudio(std::span<const int16_t> samples) {}

void PicoAudioSink::core1Task() {
    if (const auto ptr = reinterpret_cast<PicoAudioSink*>(multicore_fifo_pop_blocking()); ptr != nullptr) {
        printf("TEST");
        ptr->playbackLoop();
    }
}

void PicoAudioSink::playbackLoop() const {
    while (running.load()) {
    }
}
