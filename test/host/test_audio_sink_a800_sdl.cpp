
#include "sdl_audio_sink.hpp"
#include "atari800_pokey.hpp"
#include "test_audio_sink_a800.hpp"

int main() {
    constexpr int bufferSize = 512;
    constexpr int sampleRate = 44100;
    const SDLAudioSink sink(sampleRate, bufferSize);
    const Atari800Pokey pokey(sampleRate, bufferSize, 0);

    test_audio_sink_a800(sink, pokey);
    return 0;
}
