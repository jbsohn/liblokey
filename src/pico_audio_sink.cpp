#include "pico_audio_sink.hpp"
#include "pico/stdlib.h"

PicoAudioSink::PicoAudioSink(const uint32_t sampleRate, const uint gpioPin)
    : sampleRate(sampleRate), sampleDelayUS(1'000'000 / sampleRate), gpioPin(gpioPin) {
    initGPIO();
}

void PicoAudioSink::initGPIO() {
    gpio_init(gpioPin);
    gpio_set_dir(gpioPin, GPIO_OUT);
    gpio_put(gpioPin, 0);
}

void PicoAudioSink::start() {
    // No-op for now — you could use this to prepare DMA or timers later
}

void PicoAudioSink::stop() {
    gpio_put(gpioPin, 0);  // silence
}

void PicoAudioSink::writeAudio(tcb::span<const int16_t> samples) {
    for (int16_t s : samples) {
        outputSample(s);
        sleep_us(sampleDelayUS);
    }
}

void PicoAudioSink::outputSample(int16_t sample) {
    // Convert signed 16-bit to 8-bit unsigned PWM-style
    uint8_t pwmValue = static_cast<uint8_t>((sample + 32768) >> 8);  // 16-bit to 8-bit
    gpio_put(gpioPin, pwmValue > 127);                               // crude 1-bit PWM for now
}
