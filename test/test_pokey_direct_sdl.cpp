#include <SDL.h>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "pokey/pokeysnd.h"
#include "pokey_register.hpp"

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512

void play_engine_drone() {
    POKEYSND_Update(addr(PokeyRegister::AUDF1), 0x40, 0, 1);
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0xAF, 0, 1);
    SDL_Delay(500);
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void play_force_field_buzz() {
    for (int i = 0; i < 16; ++i) {
        const int pitch = i % 2 == 0 ? 0x30 : 0x34;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), 0xAF, 0, 1);
        SDL_Delay(50);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void play_alert_siren() {
    for (int r = 0; r < 2; ++r) {
        for (int i = 0x20; i < 0x60; ++i) {
            POKEYSND_Update(addr(PokeyRegister::AUDF1), i, 0, 1);
            POKEYSND_Update(addr(PokeyRegister::AUDC1), 0xAF, 0, 1);
            SDL_Delay(8);
        }
        for (int i = 0x60; i > 0x20; --i) {
            POKEYSND_Update(addr(PokeyRegister::AUDF1), i, 0, 1);
            SDL_Delay(8);
        }
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void play_alien_squelch(std::default_random_engine &rng) {
    std::uniform_int_distribution dist64(0, 63);
    std::uniform_int_distribution dist2(0, 1);
    for (int i = 0; i < 20; ++i) {
        const int freq = 0x10 + dist64(rng);
        const int style = dist2(rng) ? 0x8F : 0xAF;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), freq, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), style, 0, 1);
        SDL_Delay(40);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void play_laser_blast() {
    for (int i = 0; i < 16; ++i) {
        const int pitch = 0x70 - i * 3;
        const int volume = 0x0F - (i / 2);
        int audc = 0xA0 | volume & 0x0F;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        SDL_Delay(20);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void play_explosion(std::default_random_engine &rng) {
    std::uniform_int_distribution dist40(0x20, 0x5F);
    std::uniform_int_distribution dist3(0, 2);
    for (int i = 0; i < 24; ++i) {
        const int noise = dist40(rng);
        int audc = dist3(rng) == 0 ? 0x8F : 0xAF;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), noise, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDF2), noise ^ 0x3F, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC2), 0x8F, 0, 1);
        SDL_Delay(30);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
    POKEYSND_Update(addr(PokeyRegister::AUDC2), 0x00, 0, 1);
}

void play_electric_zap(std::default_random_engine &rng) {
    std::uniform_int_distribution dist32(0, 31);
    for (int i = 0; i < 12; ++i) {
        const int pitch = 0x10 + dist32(rng);
        const int volume = 0x0F - (i / 3);
        int audc = 0xC0 | volume & 0x0F; // more distortion
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        SDL_Delay(25);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void play_glitch_sweep(std::default_random_engine &rng) {
    std::uniform_int_distribution dist64(0, 63);
    std::uniform_int_distribution dist32(0, 31);
    for (int i = 0; i < 20; ++i) {
        const int glitch_freq = dist64(rng) ^ dist32(rng);
        int audc = i % 2 == 0 ? 0x9F : 0x8E;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), glitch_freq, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        SDL_Delay(22);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void run_all_effects() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    play_engine_drone();
    play_force_field_buzz();
    play_alert_siren();
    play_alien_squelch(rng);
    play_laser_blast();
    play_explosion(rng);
    play_electric_zap(rng);
    play_glitch_sweep(rng);
}

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
    run_all_effects();
    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}