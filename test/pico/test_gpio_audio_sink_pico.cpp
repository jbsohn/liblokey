#include <memory>
#include "pico_gpio_audio_sink.hpp"
#include "pico/bootrom.h"
#include "test_audio_sink.hpp"

int main() {
    constexpr int sampleRate = 44100;
    PicoGpioAudioSink sink(0, sampleRate);
    test_audio_sink(sink);
    reset_usb_boot(0, 0);
}
