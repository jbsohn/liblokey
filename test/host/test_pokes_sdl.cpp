
#include "audio/sdl_audio_sink.hpp"
#include "test_pokey_trace.hpp"
#include "pokey/prosystem_pokey.hpp"

int main() {
    constexpr int bufferSize = 256;
    constexpr int sampleRate = 44100;
    SDLAudioSink sink(sampleRate, bufferSize);
    ProSystemPokey pokey(sampleRate);

    sink.start();
    for (auto event : pokeyEvents) {
        pokey.poke(static_cast<PokeyRegister>(event.reg), event.val);
        sink.writeAudio(pokey.renderAudio());
    }
    sink.stop();
    return 0;
}
