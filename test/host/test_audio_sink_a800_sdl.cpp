
#include "sdl_audio_sink.hpp"
#include "atari800_pokey.hpp"
#include "prosystem_pokey.hpp"
#include "test_audio_sink_a800.hpp"

constexpr int bufferSize = 512;
constexpr int sampleRate = 22050;

void testAtari800() {
    printf("Atari800 testing started\n");
    SDLAudioSink sink(sampleRate, bufferSize);
    Atari800Pokey pokey(sampleRate, bufferSize, 0);
    testAudioSinkA800(sink, pokey);
    printf("Atari800 testing done\n");
}

void testProSystem() {
    printf("ProSystem testing started\n");
    SDLAudioSink sink(sampleRate, bufferSize);
    ProSystemPokey pokey(sampleRate);
    testAudioSinkA800(sink, pokey);
    printf("ProSystem test finished\n");
}

int main() {
    testProSystem();
    testAtari800();
    return 0;
}
