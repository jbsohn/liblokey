#include "pico/bootrom.h"
#include "audio/pico_pwm_audio_sink.hpp"
#include "test_audio_sink.hpp"

int main() {
    constexpr int sampleRate = 44100;
    PicoPwmAudioSink sink(18, 12, sampleRate);
    testAudioSink(sink);
    reset_usb_boot(0, 0);
}
