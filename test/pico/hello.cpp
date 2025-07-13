#include "pico/stdlib.h"
#include <cstdio>

[[noreturn]] int main() {
    stdio_init_all();

    constexpr uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        printf("Hello, Pico!\n");
        gpio_put(LED_PIN, true);  // Turn LED on
        sleep_ms(1000);
        gpio_put(LED_PIN, false);  // Turn LED off
        sleep_ms(1000);
    }
}
