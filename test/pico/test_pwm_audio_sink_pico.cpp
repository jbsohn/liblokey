#include "pico/bootrom.h"
#include "audio/pico_pwm_audio_sink.hpp"
#include "test_audio_sink.hpp"

int main() {
    constexpr int AUDIO_PIN = 18;
    constexpr int SAMPLE_RATE = 44100;

    PicoPwmAudioSink sink(AUDIO_PIN, 12, SAMPLE_RATE);
    testAudioSink(sink);
    reset_usb_boot(0, 0);
}
