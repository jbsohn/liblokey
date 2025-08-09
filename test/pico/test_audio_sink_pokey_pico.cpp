#include <cstdio>
#include "pico/stdio.h"
#include "pico/bootrom.h"
#include "pokey/prosystem_pokey.hpp"
#include "audio/pico_pwm_audio_sink.hpp"
#include "test_audio_sink_pokey.hpp"

int main() {
    stdio_init_all();
    constexpr int bufferSize = 16;
    constexpr int sampleRate = 44100;
    auto pokey = ProSystemPokey(sampleRate);
    auto picoAudioSink = PicoPwmAudioSink(0, 13u, sampleRate, bufferSize, 4);

    printf("Starting PicoAudioSink tests...\n");
    printf("Sample Rate: %d, Buffer Size: %d\n", sampleRate, bufferSize);

    printf("PicoAudioSink test...\n");
    testAudioSinkPokey(picoAudioSink, pokey);
    reset_usb_boot(0, 0);
    return 0;
}
