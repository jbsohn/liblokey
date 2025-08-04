#pragma once

#include "audio_sink.hpp"

constexpr int sampleRate = 44100;
constexpr int bufferSize = 512;

void testAudioSink(AudioSink& sink);
