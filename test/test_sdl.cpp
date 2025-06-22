#include <SDL.h>
#include <stdio.h>
#include <unistd.h>
#include "lokey.hpp"

void audio_callback(void* userdata, Uint8* stream, int len) {
    float* fstream = (float*)stream;
    int frames = len / sizeof(float); // assuming mono 32-bit float samples

    auto *lokey = static_cast<Lokey*>(userdata);
    lokey->render(fstream, frames);
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    Lokey lokey(44100, 1);

    SDL_AudioSpec spec = {44100, AUDIO_F32SYS, 1, 0, 512, 0, 0, audio_callback, &lokey};
    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        printf("SDL_OpenAudio failed: %s\n", SDL_GetError());
        return 1;
    }
    lokey.writeRegister(POKEY_OFFSET_AUDF1, 0xF0);
    lokey.writeRegister(POKEY_OFFSET_AUDC1, 0xA0);

    SDL_PauseAudio(0);
    SDL_Delay(3000);
    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}
