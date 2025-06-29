#pragma once

#include <SDL.h>
#include <tcb/span.hpp>
#include "audio_sink.hpp" // where AudioSink is declared

class SDLAudioSink final : public AudioSink {
public:
    explicit SDLAudioSink(int sampleRate = 44100, int bufferFrames = 512);
    ~SDLAudioSink() override;

    void start() override;
    void stop() override;
    void writeAudio(tcb::span<const int16_t> samples) override;

    [[nodiscard]] const char* name() const override {
        return "SDLAudioSink";
    }

private:
    SDL_AudioDeviceID deviceId = 0;
    uint32_t targetQueuedBytes = 0;
    bool running = false;
    bool isValid = false;
};
