
#include "audio/sdl_audio_sink.hpp"
#include "pokey/atari800_pokey.hpp"
#include "pokey/prosystem_pokey.hpp"
#include "test_audio_sink_pokey.hpp"

#include <chrono>

constexpr int bufferSize = 256;
constexpr int sampleRate = 22050;

inline uint64_t now_ms() {
#ifdef PICO_ON_DEVICE
    return to_ms_since_boot(get_absolute_time());
#else
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
#endif
}

void testAtari800() {
    printf("Atari800 testing started\n");
    SDLAudioSink sink(sampleRate, bufferSize);
    Atari800Pokey pokey(sampleRate, bufferSize, 0);
    testAudioSinkPokey(sink, pokey);
    printf("Atari800 testing done\n");
}

void testProSystem() {
    printf("ProSystem testing started\n");
    SDLAudioSink sink(sampleRate, bufferSize);
    ProSystemPokey pokey(sampleRate);
    testAudioSinkPokey(sink, pokey);
    printf("ProSystem test finished\n");
}

int main() {
    testProSystem();
    testAtari800();
    return 0;
}
