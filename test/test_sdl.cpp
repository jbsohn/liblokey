#include <SDL.h>
#include <cstdio>
#include "lokey.hpp"

static constexpr int SAMPLE_RATE = 44100;
static constexpr int BUFFER_SIZE = 512;

void audioCallback(void* userdata, Uint8* stream, int len) {
    auto* buffer = reinterpret_cast<int16_t*>(stream);
    const int samples = len / sizeof(int16_t);

    Lokey::instance().render(buffer, samples);
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if (!Lokey::instance().init(SAMPLE_RATE)) {
        std::fprintf(stderr, "Lokey::init() failed\n");
        return 1;
    }

    SDL_AudioSpec spec{};
    spec.freq = SAMPLE_RATE;
    spec.format = AUDIO_S16SYS;
    spec.channels = 1;
    spec.samples = BUFFER_SIZE;
    spec.callback = audioCallback;

    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        std::fprintf(stderr, "SDL_OpenAudio failed: %s\n", SDL_GetError());
        return 1;
    }

    // Set up a basic square wave tone
    Lokey::instance().poke(PokeyRegister::AUDF1, 0x28);   // ~440 Hz
    Lokey::instance().poke(PokeyRegister::AUDC1, 0xA0);   // Pure tone, volume=10
    Lokey::instance().reset_registers();

    SDL_PauseAudio(0);  // Start audio playback

    printf("Running... press Ctrl+C to quit\n");

    while (true) {
        SDL_Delay(1000);  // Just idle
    }

    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}