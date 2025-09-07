#include <cstdio>
#include "audio/pico_pwm_audio_sink.hpp"
#include "pokey/prosystem_pokey.hpp"
#include "test_pokey_trace.hpp"
#include "pico/bootrom.h"
#include "pico/stdio.h"

int main() {
    constexpr int bufferSize = 16;
    constexpr int sampleRate = 22050;

    stdio_init_all();
    printf("starting audio sink...\n");
    PicoPwmAudioSink sink(18, 8u, sampleRate, bufferSize, 8);
    sink.start();

    printf("starting pokey...\n");
    ProSystemPokey pokey(sampleRate);

    for (auto event : pokeyEvents) {
        pokey.poke(static_cast<PokeyRegister>(event.reg), event.val);
        sink.writeAudio(pokey.renderAudio());
    }
    sink.stop();
    reset_usb_boot(0, 0);
}
