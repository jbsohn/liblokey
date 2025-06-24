
// platform.c
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sound.h"
#include "platform.h"

#define SAMPLE_RATE 44100

int Atari800_tv_mode = 0; // 0 = NTSC, 1 = PAL (default to NTSC for 7800)
int ESC_enable_sio_patch = 0;
int PBI_IRQ = 0;
int PIA_IRQ = 0;
int CPU_IRQ = 0;
int Atari800_turbo = 0;


/*
void LOKEY_SoundInit(void) {
    Sound_desired.freq = SAMPLE_RATE;
    Sound_desired.sample_size = 2;     // 16-bit signed
    Sound_desired.channels = 1;        // mono
    Sound_desired.buffer_ms = 32;      // target ~32ms latency
    Sound_desired.buffer_frames = 0;   // let backend choose

    if (!Sound_Setup()) {
        fprintf(stderr, "Sound_Setup() failed!\n");
        exit(1);
    }
}
 */

static void SoundCallback(void *userdata, uint8_t *stream, int len)
{
    Sound_Callback(stream, len);
}

int PLATFORM_SoundSetup(Sound_setup_t *setup)
{
    // SDL_AudioSpec desired;
    //
    // if (Sound_enabled)
    //     SDL_CloseAudio();
    // else if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    //     Log_print("SDL_INIT_AUDIO FAILED: %s", SDL_GetError());
    //     return FALSE;
    // }
    //
    // desired.freq = setup->freq;
    // desired.format = setup->sample_size == 2 ? AUDIO_S16SYS : AUDIO_U8;
    // desired.channels = setup->channels;
    //
    // if (setup->buffer_frames == 0)
    //     /* Set buffer_frames automatically. */
    //         setup->buffer_frames = setup->freq / 50;
    //
    // setup->buffer_frames = Sound_NextPow2(setup->buffer_frames);
    //
    // desired.samples = setup->buffer_frames;
    // desired.callback = SoundCallback;
    // desired.userdata = NULL;
    //
    // if (SDL_OpenAudio(&desired, NULL) < 0) {
    //     SDL_QuitSubSystem(SDL_INIT_AUDIO);
    //     return FALSE;
    // }
    // setup->buffer_frames = desired.samples;

    return TRUE;
}

void PLATFORM_SoundExit(void)
{
    // SDL_CloseAudio();
    // SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void PLATFORM_SoundPause(void)
{
    // SDL_PauseAudio(1);
}

void PLATFORM_SoundContinue(void)
{
    // SDL_PauseAudio(0);
}

void PLATFORM_SoundLock(void)
{
    // SDL_LockAudio();
}

void PLATFORM_SoundUnlock(void)
{
    // SDL_UnlockAudio();
}
