#include "pokey.h"

float pokey_generate_sample() {
    // Simulated internal state for one channel
    static int divider = 60;         // Controls frequency (like AUDF1)
    static int volume = 12;          // Simulated volume (0–15)
    static int counter = 0;
    static int phase = 0;

    // Optional melody pattern
    static int melody[] = { 60, 50, 40, 35, 30, 25, 20 };
    static int note = 0;
    static int ticks = 0;

    // Advance note every ~1 second (assuming 44.1kHz)
    ticks++;
    if (ticks % 44100 == 0) {
        note = (note + 1) % (sizeof(melody) / sizeof(melody[0]));
        divider = melody[note];
    }

    // Simple square wave
    counter++;
    if (counter >= divider * 2) {
        counter = 0;
        phase = !phase;
    }

    return (phase ? 1.0f : -1.0f) * (volume / 15.0f);
}
