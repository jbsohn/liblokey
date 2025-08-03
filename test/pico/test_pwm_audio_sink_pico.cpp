#include "pico/bootrom.h"
#include "test_audio_sink.hpp"
#include "pico_pwm_audio_sink.hpp"
#include "test_audio_sink.hpp"

int main() {
    constexpr int sampleRate = 44100;
    PicoPwmAudioSink sink(0, 12, sampleRate);
    test_audio_sink(sink);
    reset_usb_boot(0, 0);
}
