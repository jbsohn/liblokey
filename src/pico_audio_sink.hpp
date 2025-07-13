#pragma once

#include "audio_sink.hpp"

class PicoAudioSink final : public AudioSink {
public:
    PicoAudioSink(uint32_t sampleRate, int gpioPin);
    ~PicoAudioSink() override;

    void start() override;
    void stop() override;
    void writeAudio(tcb::span<const int16_t> samples) override;

    [[nodiscard]] uint32_t getSampleRate() const override {
        return sampleRate;
    }
    [[nodiscard]] const char* name() const override {
        return "";
    }

private:
    const uint32_t sampleRate;
    const int gpioPin;
};