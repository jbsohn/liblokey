#include <cstdio>
#include "audio/pico_pwm_audio_sink.hpp"
#include "pokey/prosystem_pokey.hpp"
#include "test_pokey_trace.hpp"
#include "pico/bootrom.h"
#include "pico/stdio.h"

int main() {
    constexpr int AUDIO_PIN = 18;
    constexpr int BUFFER_SIZE = 16;
    constexpr int SAMPLE_RATE = 22050;

    stdio_init_all();
    printf("starting audio sink...\n");

    PicoPwmAudioSink sink(AUDIO_PIN, 8u, SAMPLE_RATE, BUFFER_SIZE, 8);
    sink.start();

    printf("starting pokey...\n");
    ProSystemPokey pokey(SAMPLE_RATE);

    for (auto event : pokeyEvents) {
        pokey.poke(static_cast<PokeyRegister>(event.reg), event.val);
        sink.writeAudio(pokey.renderAudio());
    }
    sink.stop();
    reset_usb_boot(0, 0);
}
