#include "lokey.h"
#include <SDL.h>
#include <stdio.h>

void audio_callback(void* userdata, Uint8* stream, int len) {
    lokey_render_audio((float*)stream, len / sizeof(float));
}

int main() {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec spec = {44100, AUDIO_F32SYS, 1, 0, 512, 0, 0, audio_callback, nullptr};
    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        printf("SDL_OpenAudio failed: %s\n", SDL_GetError());
        return 1;
    }
    lokey_init(44100, 1);
    SDL_PauseAudio(0);
    SDL_Delay(3000);
    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}
