
#include "sdl_audio_sink.hpp"
#include "atari800_pokey.hpp"
#include "test_data.hpp"

int main() {
    constexpr int bufferSize = 1024;
    constexpr int sampleRate = 44100;
    SDLAudioSink sink(sampleRate, bufferSize);
    Atari800Pokey pokey(sampleRate, bufferSize, 0);

    sink.start();
    constexpr int pokes_per_frame = 6;
    for (size_t i = 0; i < pokes.size(); i += pokes_per_frame) {
        for (size_t j = 0; j < pokes_per_frame && i + j < pokes.size(); ++j) {
            auto& [address, value] = pokes[i + j];
            pokey.poke(static_cast<PokeyRegister>(address), value);
        }
        const auto samples = pokey.renderAudio();
        sink.writeAudio(samples);
    }
    sink.stop();
    return 0;
}
