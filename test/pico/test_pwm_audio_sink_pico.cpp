#include "pico/bootrom.h"
#include "audio/pico_pwm_audio_sink.hpp"
#include "test_audio_sink.hpp"

int main() {
    constexpr int sampleRate = 44100;
    constexpr int AUDIO_PIN = 18;

    PicoPwmAudioSink sink(AUDIO_PIN, 12, sampleRate);
    testAudioSink(sink);
    reset_usb_boot(0, 0);
}
