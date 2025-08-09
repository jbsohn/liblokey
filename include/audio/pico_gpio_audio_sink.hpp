#pragma once

#include <cstdint>
#include <span>
#include "audio_sink.hpp"
#include "pico/util/queue.h"

class PicoGpioAudioSink final : public AudioSink {
public:
    explicit PicoGpioAudioSink(uint gpio_pin, uint32_t sample_rate = 22050);
    ~PicoGpioAudioSink() override;

    void start() override;
    void stop() override;
    void writeAudio(std::span<const int16_t> samples) override;
    [[nodiscard]] uint32_t getSampleRate() const override {
        return sample_rate;
    }
    size_t getQueueLevel() {
        return queue_get_level(&sampleQueue);
    }

private:
    uint gpio_pin;
    uint32_t sample_rate;
    bool running = false;
    queue_t sampleQueue{};

    static constexpr int kBufferSize = 256;  // samples per buffer
    static constexpr int kQueueLength = 8;   // buffers in queue

    static void core1Task();
};
