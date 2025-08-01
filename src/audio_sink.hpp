#pragma once

#include <cstdint>
#include <span>

class AudioSink {
public:
    virtual ~AudioSink() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void writeAudio(std::span<const int16_t> samples) = 0;
    [[nodiscard]] virtual uint32_t getSampleRate() const {
        return 0;
    }
    [[nodiscard]] virtual size_t getBufferSize() {
        return 0;
    }
    [[nodiscard]] virtual const char* name() const {
        return "UnnamedAudioSink";
    }
};
