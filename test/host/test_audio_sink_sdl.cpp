#include "test_audio_sink.hpp"
#include "sdl_audio_sink.hpp"

int main() {
    SDLAudioSink sink(sampleRate, bufferSize);
    test_audio_sink(sink);
    return 0;
}