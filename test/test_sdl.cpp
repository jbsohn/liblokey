#include <SDL.h>
#include <cstdio>
#include <cstdlib>
#include "pokey/pokeysnd.h"

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512

void audio_callback(void *userdata, Uint8 *stream, int len) {
    POKEYSND_Process(stream, len / 2); // 16-bit: len in bytes → samples
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec desired, obtained;
    SDL_zero(desired);
    desired.freq = SAMPLE_RATE;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    desired.samples = BUFFER_SIZE;
    desired.callback = audio_callback;

    if (SDL_OpenAudio(&desired, &obtained) < 0) {
        fprintf(stderr, "SDL_OpenAudio failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_ClearQueuedAudio(1);

    POKEYSND_Init(POKEYSND_FREQ_17_APPROX, SAMPLE_RATE, 1, POKEYSND_BIT16);

    SDL_PauseAudio(0); // start playback

    POKEYSND_Update(0x01, 0xAF, 0, 1);  // AUDC0: volume = 15, tone enable
    POKEYSND_Update(0x00, 0x28, 0, 1);  // AUDF0: divisor for pitch
    POKEYSND_Update(0x08, 0x03, 0, 1);  // SKCTL: enable sound
    POKEYSND_Update(0x03, 0xAF, 0, 1);  // AUDC1
    POKEYSND_Update(0x05, 0xAF, 0, 1);  // AUDC2
    POKEYSND_Update(0x07, 0xAF, 0, 1);  // AUDC3

    for (int i = 0; i < 16; ++i) {
        constexpr int base_freq = 0x60;
        POKEYSND_Update(0x00, base_freq - i, 0, 1);  // AUDF0
        POKEYSND_Update(0x02, base_freq - i - 4, 0, 1);  // AUDF1
        POKEYSND_Update(0x04, base_freq - i - 8, 0, 1);  // AUDF2
        POKEYSND_Update(0x06, base_freq - i - 12, 0, 1); // AUDF3
        SDL_Delay(50);
    }

    SDL_Delay(1500);

    for (int i = 0x28; i < 0x80; ++i) {
        POKEYSND_Update(0x00, i, 0, 1);  // AUDF0
        POKEYSND_Update(0x02, i + 4, 0, 1);  // AUDF1
        POKEYSND_Update(0x04, i + 8, 0, 1);  // AUDF2
        POKEYSND_Update(0x06, i + 12, 0, 1); // AUDF3
        SDL_Delay(30);
    }

    SDL_Delay(1500);

    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}