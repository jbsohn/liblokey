#include <cstring>
#include <vector>
#include <algorithm>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pwm.h"
#include "audio/pico_pwm_audio_sink.hpp"

PicoPwmAudioSink::PicoPwmAudioSink(const uint gpioPin,
                                   const uint pwmBits,
                                   const uint32_t sampleRate,
                                   const size_t bufferSize,
                                   const size_t queueLength)
    : gpioPin(gpioPin), pwmBits(pwmBits), sampleRate(sampleRate), bufferSize(bufferSize), queueLength(queueLength) {
    queue_init(&sampleQueue, bufferSize * sizeof(int16_t), queueLength);
}

PicoPwmAudioSink::~PicoPwmAudioSink() {
    PicoPwmAudioSink::stop();
    queue_free(&sampleQueue);
}

void PicoPwmAudioSink::start() {
    if (running) {
        return;
    }
    running = true;
    multicore_launch_core1(core1Task);
    multicore_fifo_push_blocking(reinterpret_cast<uintptr_t>(this));
}

void PicoPwmAudioSink::stop() {
    if (!running) {
        return;
    }
    running = false;
    sleep_ms(10);
}

void PicoPwmAudioSink::writeAudio(const std::span<const int16_t> samples) {
    if (!running || samples.empty()) {
        return;
    }

    size_t offset = 0;
    while (offset < samples.size()) {
        std::vector<int16_t> buffer(bufferSize);
        const size_t chunk = std::min(bufferSize, samples.size() - offset);
        std::memcpy(buffer.data(), samples.data() + offset, chunk * sizeof(int16_t));
        queue_add_blocking(&sampleQueue, buffer.data());
        offset += chunk;
    }
}

void PicoPwmAudioSink::core1Task() {
    auto* sink = reinterpret_cast<PicoPwmAudioSink*>(multicore_fifo_pop_blocking());
    if (sink == nullptr) {
        return;
    }

    gpio_set_function(sink->gpioPin, GPIO_FUNC_PWM);
    const uint slice_num = pwm_gpio_to_slice_num(sink->gpioPin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.0f);
    pwm_config_set_wrap(&config, (1u << sink->pwmBits) - 1);
    pwm_init(slice_num, &config, true);

    std::vector<int16_t> buffer(sink->bufferSize);
    const uint16_t pwm_max = (1u << sink->pwmBits) - 1;
    const float us_per_sample = 1'000'000.0f / sink->sampleRate;

    while (sink->running) {
        queue_remove_blocking(&sink->sampleQueue, buffer.data());
        for (size_t i = 0; i < sink->bufferSize && sink->running; ++i) {
            const float scaled = static_cast<float>(buffer[i]) / 32768.0f;
            const float biased = (scaled + 1.0f) * 0.5f;
            const uint16_t pwm_val = std::clamp<int>(biased * pwm_max, 0, pwm_max);
            pwm_set_gpio_level(sink->gpioPin, pwm_val);
            sleep_us(static_cast<uint32_t>(us_per_sample));
        }
    }
    pwm_set_gpio_level(sink->gpioPin, 0);
}
