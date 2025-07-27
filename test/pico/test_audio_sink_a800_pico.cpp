#include "pico/time.h"
#include "pico/bootrom.h"
#include "atari800_pokey.hpp"
#include "null_audio_sink.hpp"
#include "pico_audio_sink.hpp"
#include "util.hpp"
#include "pico/stdio_usb.h"

void playTone(Pokey& pokey, AudioSink& sink, uint8_t audf, uint8_t audc, int ms) {
    pokey.poke(PokeyRegister::AUDF1, audf, 1);
    pokey.poke(PokeyRegister::AUDC1, audc, 1);

    const absolute_time_t end = make_timeout_time_ms(ms);
    while (absolute_time_diff_us(get_absolute_time(), end) > 0) {
        sink.writeAudio(pokey.renderAudio());
    }
}

void sinkTest(Pokey& pokey, AudioSink& sink) {
    PicoTimeIt t{};
    sink.start();

    // Soft tone 1
    pokey.poke(PokeyRegister::AUDCTL, 0x00, 1);
    pokey.poke(PokeyRegister::AUDC1, 0xA2, 1);
    playTone(pokey, sink, 0x50, 0xA2, 800);  // lower tone

    // Soft tone 2
    playTone(pokey, sink, 0x30, 0xA4, 800);  // mid tone, slightly louder

    // Soft tone 3
    playTone(pokey, sink, 0x20, 0xA6, 800);  // higher tone

    // Silence
    pokey.poke(PokeyRegister::AUDC1, 0x00, 1);
}

int main() {
    stdio_usb_init();
    while (!stdio_usb_connected()) {
        tight_loop_contents();
    }

    constexpr int bufferSize = 512;
    constexpr int sampleRate = 22050;
    auto pokey = Atari800Pokey(sampleRate, bufferSize, 0);
    auto nullAudioSink = NullAudioSink{};
    auto picoAudioSink = PicoAudioSink{0, sampleRate, bufferSize};

    printf("PicoAudioSink test...\n");
    sinkTest(pokey, picoAudioSink);

    printf("NullAudioSink test...\n");
    sinkTest(pokey, nullAudioSink);

    reset_usb_boot(0, 0);
    return 0;
}