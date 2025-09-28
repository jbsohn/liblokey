#include <memory>
#include "audio/pico_gpio_audio_sink.hpp"
#include "pico/bootrom.h"
#include "test_audio_sink.hpp"

int main() {
    constexpr int AUDIO_PIN = 18;
    constexpr int SAMPLE_RATE = 44100;
    PicoGpioAudioSink sink(AUDIO_PIN, SAMPLE_RATE);

    testAudioSink(sink);
    reset_usb_boot(0, 0);
}
