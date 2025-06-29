#include <fmt/format.h>
#include "sdl_audio_sink.hpp"

SDLAudioSink::SDLAudioSink(const int sampleRate, const int bufferFrames) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fmt::print(stderr, "SDLAudioSink: Failed to initialize SDL audio: {}\n", SDL_GetError());
        return;
    }

    SDL_AudioSpec want;
    SDL_zero(want);
    want.freq = sampleRate;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = bufferFrames;
    want.callback = nullptr;

    deviceId = SDL_OpenAudioDevice(nullptr, 0, &want, &spec, 0);
    if (deviceId == 0) {
        fmt::print(stderr, "SDLAudioSink: SDLAudioSink: Failed to open audio device: {}\n", SDL_GetError());
    }
}

SDLAudioSink::~SDLAudioSink() {
    if (deviceId != 0) {
        SDLAudioSink::stop(); // Ensure the device is paused before closing
        SDL_CloseAudioDevice(deviceId);
    }
    // Only quit the subsystem we initialized.
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SDLAudioSink::start() {
    if (deviceId != 0 && !running) {
        SDL_PauseAudioDevice(deviceId, 0); // 0 means unpause (start playback)
        running = true;
    }
}

void SDLAudioSink::stop() {
    if (deviceId != 0 && running) {
        SDL_PauseAudioDevice(deviceId, 1); // 1 means pause
        running = false;
    }
}

void SDLAudioSink::writeAudio(tcb::span<const int16_t> samples) {
    if (deviceId == 0 || samples.empty()) {
        return;
    }

    if (SDL_QueueAudio(deviceId, samples.data(), samples.size_bytes()) < 0) {
        fmt::print(stderr, "SDLAudioSink: SDLAudioSink: Failed to open audio device: {}\n", SDL_GetError());
    }
}