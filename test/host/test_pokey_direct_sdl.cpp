#include <SDL.h>
#include <random>
#include <thread>
#include <fmt/format.h>
#include "atari800_pokey/pokeysnd.h"
#include "pokey/pokey_register.hpp"

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512

void playEngineDrone() {
    POKEYSND_Update(addr(PokeyRegister::AUDF1), 0x40, 0, 1);
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0xAF, 0, 1);
    SDL_Delay(500);
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void playForceFieldBuzz() {
    for (int i = 0; i < 16; ++i) {
        const int pitch = i % 2 == 0 ? 0x30 : 0x34;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), 0xAF, 0, 1);
        SDL_Delay(50);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void playAlertSiren() {
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

void playAlienSquelch(std::default_random_engine& rng) {
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

void playLaserBlast() {
    for (int i = 0; i < 16; ++i) {
        const int pitch = 0x70 - i * 3;
        const int volume = 0x0F - (i / 2);
        const int audc = 0xA0 | (volume & 0x0F);
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        SDL_Delay(20);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void playExplosion(std::default_random_engine& rng) {
    std::uniform_int_distribution<> dist40(0x20, 0x5F);
    std::uniform_int_distribution<> dist3(0, 2);
    for (int i = 0; i < 24; ++i) {
        const int noise = dist40(rng);
        const int audc = dist3(rng) == 0 ? 0x8F : 0xAF;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), noise, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDF2), noise ^ 0x3F, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC2), 0x8F, 0, 1);
        SDL_Delay(30);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
    POKEYSND_Update(addr(PokeyRegister::AUDC2), 0x00, 0, 1);
}

void playElectricZap(std::default_random_engine& rng) {
    std::uniform_int_distribution<> dist32(0, 31);
    for (int i = 0; i < 12; ++i) {
        const int pitch = 0x10 + dist32(rng);
        const int volume = 0x0F - (i / 3);
        const int audc = 0xC0 | (volume & 0x0F);  // more distortion
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        SDL_Delay(25);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void playGlitchSweep(std::default_random_engine& rng) {
    std::uniform_int_distribution<> dist64(0, 63);
    std::uniform_int_distribution<> dist32(0, 31);
    for (int i = 0; i < 20; ++i) {
        const int glitch_freq = dist64(rng) ^ dist32(rng);
        int audc = i % 2 == 0 ? 0x9F : 0x8E;
        POKEYSND_Update(addr(PokeyRegister::AUDF1), glitch_freq, 0, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), audc, 0, 1);
        SDL_Delay(22);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 0, 1);
}

void runAllEffects() {
    std::random_device rd;

    std::default_random_engine rng(rd());
    playEngineDrone();
    playForceFieldBuzz();
    playAlertSiren();
    playAlienSquelch(rng);
    playLaserBlast();
    playExplosion(rng);
    playElectricZap(rng);
    playGlitchSweep(rng);
}

void backgroundEngineVibrato() {
    for (int i = 0; i < 120; ++i) {
        const int pitch = 0x30 + i / 4 % 6;  // Subtle vibrato
        POKEYSND_Update(addr(PokeyRegister::AUDF1), pitch, 1, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), 0xAF, 1, 1);
        SDL_Delay(25);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 1, 1);
}

void backgroundLfoSweep() {
    for (int i = 0; i < 100; ++i) {
        const int mod = 0x10 + (i % 20 ^ i >> 2);
        POKEYSND_Update(addr(PokeyRegister::AUDF2), mod, 1, 1);
        POKEYSND_Update(addr(PokeyRegister::AUDC2), 0xCF, 1, 1);  // buzzy noise
        SDL_Delay(30);
    }
    POKEYSND_Update(addr(PokeyRegister::AUDC2), 0x00, 1, 1);
}

void backgroundHihatLoop() {
    for (int i = 0; i < 80; ++i) {
        POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x8F, 1, 1);  // noise w/ vol
        SDL_Delay(50);
        POKEYSND_Update(addr(PokeyRegister::AUDC1), 0x00, 1, 1);
        SDL_Delay(25);
    }
}

void audioCallback([[maybe_unused]] void* userdata, Uint8* stream, int len) {
    POKEYSND_Process(stream, len / 2);  // 16-bit: len in bytes → samples
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec desired, obtained;
    SDL_zero(desired);
    desired.freq = SAMPLE_RATE;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    desired.samples = BUFFER_SIZE;
    desired.callback = audioCallback;

    if (SDL_OpenAudio(&desired, &obtained) < 0) {
        printf("DL_OpenAudio failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_ClearQueuedAudio(1);
    POKEYSND_Init(POKEYSND_FREQ_17_APPROX, SAMPLE_RATE, 2, POKEYSND_BIT16);
    SDL_PauseAudio(0);  // start playback

    printf("background_hihat_loop with sound effects...\n");
    std::thread background(backgroundHihatLoop);
    runAllEffects();
    background.join();

    printf("background_lfo_sweep with sound effects...\n");
    std::thread background2(backgroundLfoSweep);
    runAllEffects();
    background2.join();

    printf("background_engine_vibrato with sound effects...\n");
    std::thread background3(backgroundEngineVibrato);
    runAllEffects();
    background3.join();

    printf("done.\n");
    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}
