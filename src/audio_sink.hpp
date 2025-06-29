#pragma once

#include <tcb/span.hpp>

class AudioSink {
public:
    virtual ~AudioSink() = default;

    virtual void writeAudio(tcb::span<const int16_t> samples) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    [[nodiscard]] virtual const char* name() const { return "UnnamedAudioSink"; }
};
