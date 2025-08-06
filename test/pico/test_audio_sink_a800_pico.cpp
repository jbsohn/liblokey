#include <cstdio>
#include "pico/stdio.h"
#include "pico/bootrom.h"
#include "atari800-pokey.hpp"
#include "pico_pwm_audio_sink.hpp"
#include "test_audio_sink_a800.hpp"

int main() {
    stdio_init_all();
    constexpr int bufferSize = 256;
    constexpr int sampleRate = 22050;
    auto pokey = Atari800Pokey(sampleRate, bufferSize, 0);
    auto picoAudioSink = PicoPwmAudioSink(0, 10u, sampleRate, bufferSize, 4);

    printf("Starting PicoAudioSink tests...\n");
    printf("Sample Rate: %d, Buffer Size: %d\n", sampleRate, bufferSize);

    printf("PicoAudioSink test...\n");
    testAudioSinkA800(picoAudioSink, pokey);
    reset_usb_boot(0, 0);
}