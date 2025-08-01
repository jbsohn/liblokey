#pragma once

#include <atomic>
#include "audio_sink.hpp"
#include "pico/util/queue.h"
#include "pico/multicore.h"

class PicoGpioAudioSink final : public AudioSink {
public:
    explicit PicoGpioAudioSink(uint gpio = 0, uint sampleRate = 22050, uint bufferSize = 2048);
    ~PicoGpioAudioSink() override;

    void start() override;
    void stop() override;
    void writeAudio(std::span<const int16_t> samples) override;
    [[nodiscard]] size_t getBufferSize() override {
        return bufferSize;
    }
    [[nodiscard]] const char* name() const override {
        return "PicoGpioAudioSink";
    }
    [[nodiscard]] uint32_t getSampleRate() const override {
        return sampleRate;
    }
    size_t getQueueLevel() {
        return queue_get_level(&sampleQueue);
    }

private:
    static void core1Task();
    void playbackLoop() const;

    uint gpio{};
    uint sampleRate{};
    std::atomic<bool> running{false};
    queue_t sampleQueue{};
    float volume = 1.0f;
    size_t bufferSize{};
};
