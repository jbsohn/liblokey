#pragma once

#include <cstdint>
#include <span>
#include "audio_sink.hpp"
#include "pico/util/queue.h"

class PicoPwmAudioSink final : public AudioSink {
public:
    explicit PicoPwmAudioSink(uint gpioPin,
                              uint pwmBits = 12,
                              uint32_t sampleRate = 44100,
                              size_t bufferSize = 128,
                              size_t queueLength = 4);
    ~PicoPwmAudioSink() override;

    void start() override;
    void stop() override;
    void writeAudio(std::span<const int16_t> samples) override;
    [[nodiscard]] const char* name() const override {
        return "PicoPwmAudioSink";
    }
    [[nodiscard]] uint32_t getSampleRate() const override {
        return sampleRate;
    }
    size_t getQueueLevel() {
        return queue_get_level(&sampleQueue);
    }

private:
    uint gpioPin;
    uint pwmBits;
    uint32_t sampleRate;
    size_t bufferSize;
    size_t queueLength;
    volatile bool running = false;
    queue_t sampleQueue{};

    static void core1Task();
};
