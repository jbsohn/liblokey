#include <thread>
#include "audio/sdl_audio_sink.hpp"

SDLAudioSink::SDLAudioSink(const int sampleRate, const int bufferFrames)
    : sampleRate(sampleRate), bufferFrames(bufferFrames) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDLAudioSink: Failed to initialize SDL audio: %d\n", SDL_GetError());
        return;
    }

    SDL_AudioSpec want;
    SDL_zero(want);
    want.freq = sampleRate;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = bufferFrames;
    want.callback = nullptr;

    SDL_AudioSpec spec{};

    deviceId = SDL_OpenAudioDevice(nullptr, 0, &want, &spec, 0);
    if (deviceId == 0) {
        printf("SDLAudioSink: Failed to open audio device: {}\n", SDL_GetError());
        return;
    }
    targetQueuedBytes = bufferFrames * sizeof(int16_t) * 4;
    isValid = true;
}

SDLAudioSink::~SDLAudioSink() {
    if (deviceId != 0) {
        SDLAudioSink::stop();
        SDL_CloseAudioDevice(deviceId);
    }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SDLAudioSink::start() {
    if (!isValid || running) {
        return;
    }
    SDL_PauseAudioDevice(deviceId, 0);
    running = true;
}

void SDLAudioSink::stop() {
    if (!isValid || !running) {
        return;
    }
    SDL_PauseAudioDevice(deviceId, 1);
    running = false;
}

void SDLAudioSink::writeAudio(std::span<const int16_t> samples) {
    if (!isValid || !running || samples.empty()) {
        return;
    }

    while (SDL_GetQueuedAudioSize(deviceId) > targetQueuedBytes) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    if (SDL_QueueAudio(deviceId, samples.data(), samples.size_bytes()) < 0) {
        printf("SDLAudioSink: Failed to queue audio: %d\n", SDL_GetError());
    }
}
