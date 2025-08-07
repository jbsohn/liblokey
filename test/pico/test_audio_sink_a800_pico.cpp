#include <cstdio>
#include "pico/stdio.h"
#include "pico/bootrom.h"
#include "atari800_pokey.hpp"
#include "prosystem_pokey.hpp"
#include "pico_pwm_audio_sink.hpp"
#include "pico_gpio_audio_sink.hpp"
#include "test_audio_sink_a800.hpp"

int main() {
    stdio_init_all();
    constexpr int bufferSize = 16;
    constexpr int sampleRate = 44100;
    auto pokey = ProSystemPokey(sampleRate);
    auto picoAudioSink = PicoPwmAudioSink(0, 13u, sampleRate, bufferSize, 4);

    printf("Starting PicoAudioSink tests...\n");
    printf("Sample Rate: %d, Buffer Size: %d\n", sampleRate, bufferSize);

    printf("PicoAudioSink test...\n");
    testAudioSinkA800(picoAudioSink, pokey);
    reset_usb_boot(0, 0);
}