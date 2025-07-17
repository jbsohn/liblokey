#include "pico_audio_sink.hpp"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

PicoAudioSink::PicoAudioSink(const uint gpio, const uint sampleRate, const uint bufferSize)
    : gpio(gpio), sampleRate(sampleRate), bufferSize(bufferSize) {
    queue_init(&sampleQueue, sizeof(int16_t), bufferSize);
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    const uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.0f);
    pwm_config_set_wrap(&config, 1023);
    pwm_init(slice, &config, true);
}

PicoAudioSink::~PicoAudioSink() {
    PicoAudioSink::stop();
    pwm_set_enabled(pwm_gpio_to_slice_num(gpio), false);
    queue_free(&sampleQueue);
}

void PicoAudioSink::start() {
    if (running)
        return;
    running = true;
    multicore_launch_core1(core1Task);
    multicore_fifo_push_blocking(reinterpret_cast<uint32_t>(this));
}

void PicoAudioSink::stop() {
    running = false;
    sleep_ms(10);
    pwm_set_enabled(pwm_gpio_to_slice_num(gpio), false);
    gpio_set_function(gpio, GPIO_FUNC_SIO);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, false);

    int16_t dummy;
    while (queue_try_remove(&sampleQueue, &dummy)) {
    }
}

void PicoAudioSink::writeAudio(const tcb::span<const int16_t> samples) {
    for (size_t i = 0; i < samples.size(); i += 16) {
        for (size_t j = 0; j < 16 && i + j < samples.size(); ++j) {
            const int16_t sample = samples[i + j];
            int32_t scaledSample = (sample * static_cast<int32_t>(volume * 256)) / 256;  // Fixed-point scaling
            if (!queue_try_add(&sampleQueue, &scaledSample)) {
                break;
            }
        }
    }
}

void PicoAudioSink::core1Task() {
    if (const auto ptr = reinterpret_cast<PicoAudioSink*>(multicore_fifo_pop_blocking())) {
        ptr->playbackLoop();
    }
}

void PicoAudioSink::playbackLoop() {
    pwm_set_enabled(pwm_gpio_to_slice_num(gpio), true);
    absolute_time_t next_sample_time = get_absolute_time();
    const uint32_t us_per_sample = 1000000 / sampleRate;
    const uint32_t us_remainder = 1000000 % sampleRate;
    uint32_t remainder_acc = 0;

    while (running) {
        int16_t sample = 0;
        if (queue_try_remove(&sampleQueue, &sample)) {
            const auto val = static_cast<int32_t>(static_cast<float>(sample) * volume);
            const uint16_t level = ((val + 32768) * 1023) / 65535;
            pwm_set_gpio_level(gpio, level);
        } else {
            pwm_set_gpio_level(gpio, 512);
        }
        next_sample_time = delayed_by_us(next_sample_time, us_per_sample);
        remainder_acc += us_remainder;
        if (remainder_acc >= sampleRate) {
            next_sample_time = delayed_by_us(next_sample_time, 1);
            remainder_acc -= sampleRate;
        }
        sleep_until(next_sample_time);
    }
}