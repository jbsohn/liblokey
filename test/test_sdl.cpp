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
    SDL_AudioSpec want = {};
    want.freq = 44100;
    want.format = AUDIO_F32SYS;
    want.channels = 1;
    want.samples = 512;
    want.callback = audio_callback;
    want.userdata = &lokey;

    const SDL_AudioDeviceID dev = SDL_OpenAudioDevice(nullptr, 0, &want, nullptr, 0);
    if (dev == 0) {
        printf("SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        return 1;
    }

    // Set up test tone (will eventually matter when pokey_process uses AUDF/AUDC)
    lokey.poke(PokeyRegister::AUDF1, 0xF0);
    lokey.poke(PokeyRegister::AUDC1, 0xA0);

    // Start audio
    SDL_PauseAudioDevice(dev, 0);

    // Play for 5 seconds
    SDL_Delay(5000);

    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    return 0;
}