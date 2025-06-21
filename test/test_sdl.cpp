#include <SDL.h>
#include <stdio.h>
#include <unistd.h>

extern "C" {
#include "lokey.h"
}

void audio_callback(void* userdata, Uint8* stream, int len) {
    float* fstream = (float*)stream;
    int frames = len / sizeof(float); // assuming mono 32-bit float samples

    lokey_render_audio(fstream, frames);
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_AudioSpec spec = {44100, AUDIO_F32SYS, 1, 0, 512, 0, 0, audio_callback, nullptr};
    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        printf("SDL_OpenAudio failed: %s\n", SDL_GetError());
        return 1;
    }
    lokey_init(44100, 1);
    lokey_write_register(0x00, 0xF0);  // AUDF1
    lokey_write_register(0x01, 0xA0);  // AUDC1
    SDL_PauseAudio(0);
    SDL_Delay(3000);
    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}
