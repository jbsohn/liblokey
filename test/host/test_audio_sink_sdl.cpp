#include "test_audio_sink.hpp"
#include "audio/sdl_audio_sink.hpp"

int main() {
    SDLAudioSink sink(sampleRate, bufferSize);
    testAudioSink(sink);
    return 0;
}