#include <SDL.h>
#include <cstdio>
#include "lokey.hpp"

void audio_callback(void* userdata, Uint8* stream, int len) {
    auto* fstream = reinterpret_cast<float*>(stream);
    const int frames = len / sizeof(float);
    auto* lokey = static_cast<Lokey*>(userdata);
    lokey->render(fstream, frames);
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    Lokey lokey(44100, 1);  // sample rate = 44100, 1 POKEY instance

    // Configure SDL audio
    SDL_AudioSpec spec = {};
    spec.freq = 44100;
    spec.format = AUDIO_F32SYS;
    spec.channels = 1;
    spec.samples = 512;
    spec.callback = audio_callback;
    spec.userdata = &lokey;

    const SDL_AudioDeviceID dev = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);
    if (dev == 0) {
        printf("SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        return 1;
    }

    lokey.poke(PokeyRegister::AUDF1, 0x28);   // Frequency divider (lower = higher pitch)
    lokey.poke(PokeyRegister::AUDC1, 0xA8);   // Pure tone, max volume
    lokey.poke(PokeyRegister::AUDCTL, 0x00);  // 64kHz clock, standard mode

    // Start audio
    SDL_PauseAudioDevice(dev, 0);

    // Play for 3 seconds
    SDL_Delay(3000);

    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    return 0;
}