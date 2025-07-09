#pragma once

#include "audio_sink.hpp"
#include <cstdint>

class PicoAudioSink : public AudioSink {
public:
    explicit PicoAudioSink(uint32_t sampleRate, uint gpioPin);

    void writeAudio(tcb::span<const int16_t> samples) override;
    void start() override;
    void stop() override;

    [[nodiscard]] const char* name() const override {
        return "PicoAudioSink";
    }

private:
    uint32_t sampleRate_;
    uint32_t sampleDelayUS_;
    uint gpioPin = 0;

    void initGPIO();
    void outputSample(int16_t sample);
};
