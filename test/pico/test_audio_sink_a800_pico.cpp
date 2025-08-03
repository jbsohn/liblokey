#include "pico/time.h"
#include "pico/bootrom.h"
#include "pico/stdio.h"
#include "atari800_pokey.hpp"
#include "null_audio_sink.hpp"
#include "pico_gpio_audio_sink.hpp"
#include "util.hpp"
#include "test_audio_sink_a800.hpp"

int main() {
    stdio_init_all();
    constexpr int bufferSize = 512;
    constexpr int sampleRate = 44100;
    auto pokey = Atari800Pokey(sampleRate, bufferSize, 0);
    auto nullAudioSink = NullAudioSink{};
    auto picoAudioSink = PicoGpioAudioSink{0, sampleRate};

    printf("PicoAudioSink test...\n");
    test_audio_sink_a800(picoAudioSink, pokey);

    printf("NullAudioSink test...\n");
    test_audio_sink_a800(nullAudioSink, pokey);

    reset_usb_boot(0, 0);
}