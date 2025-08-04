#include "pico/time.h"
#include "pico/bootrom.h"
#include "pico/stdio.h"
#include "atari800_pokey.hpp"
#include "null_audio_sink.hpp"
#include "pico_pwm_audio_sink.hpp"
#include "util.hpp"
#include "test_audio_sink_a800.hpp"

int main() {
    stdio_init_all();
    constexpr int bufferSize = 512;
    constexpr int sampleRate = 22050;
    auto pokey = Atari800Pokey(sampleRate, bufferSize, 0);
    auto picoAudioSink = PicoPwmAudioSink(0, 8U, sampleRate, bufferSize, 4);

    printf("Starting PicoAudioSink tests...\n");
    printf("Sample Rate: %d, Buffer Size: %d\n", sampleRate, bufferSize);

    printf("PicoAudioSink test...\n");
    testAudioSinkA800(picoAudioSink, pokey);
    reset_usb_boot(0, 0);
}