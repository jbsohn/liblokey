#include <cstdio>
#include "pico/stdio.h"
#include "pico/bootrom.h"
#include "pokey/prosystem_pokey.hpp"
#include "audio/pico_pwm_audio_sink.hpp"
#include "test_audio_sink_pokey.hpp"
#include "pokey/atari800_pokey.hpp"
#include "prosystem_pokey/pokey.h"

// set 1 for ProSystem, 0 for Atari800Pokey fallback
#define POKEY_PRO_SYSTEM 0
constexpr int AUDIO_PIN = 18;

int main() {
    stdio_init_all();
    int sampleRate;
    int sinkBufferSize;

    // Not sure if these are the best settings but they currently work well on the Pico
#if POKEY_PRO_SYSTEM
    sinkBufferSize = 256;
    sampleRate = 44100;
    ProSystemPokey pokey(sampleRate);
#else
    sinkBufferSize = 512;
    sampleRate = 22050;
    Atari800Pokey pokey(sampleRate, sinkBufferSize);
#endif
    PicoPwmAudioSink sink(AUDIO_PIN, 8u, sampleRate, sinkBufferSize, 8);

    printf("Starting PicoAudioSink tests...\n");
    printf("Sample Rate: %d, Buffer Size: %d\n", sampleRate, sinkBufferSize);

    printf("PicoAudioSink test...\n");
    testAudioSinkPokey(sink, pokey);

    reset_usb_boot(0, 0);
    return 0;
}
