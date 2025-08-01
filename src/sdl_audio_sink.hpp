#pragma once

#include <SDL.h>
#include "audio_sink.hpp"

class SDLAudioSink final : public AudioSink {
public:
    explicit SDLAudioSink(int sampleRate = 44100, int bufferFrames = 512);
    ~SDLAudioSink() override;

    void start() override;
    void stop() override;
    void writeAudio(std::span<const int16_t> samples) override;

    [[nodiscard]] uint32_t getSampleRate() const override {
        return sampleRate;
    }
    [[nodiscard]] const char* name() const override {
        return "SDLAudioSink";
    }

private:
    SDL_AudioDeviceID deviceId = 0;
    uint32_t targetQueuedBytes = 0;
    int sampleRate;
    int bufferFrames;
    bool running = false;
    bool isValid = false;
};
