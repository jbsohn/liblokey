#pragma once

#include "audio_sink.hpp"
#include <string>

class NullAudioSink final : public AudioSink {
public:
    void start() override {}
    void stop() override {}

    void writeAudio(const std::span<const int16_t> samples) override {
        (void)samples;
    }

    [[nodiscard]] uint32_t getSampleRate() const override {
        return 44100;
    }

    [[nodiscard]] size_t getBufferSize() override {
        return 0;
    }

    [[nodiscard]] const char* name() const override {
        return "NullAudioSink";
    }
};
