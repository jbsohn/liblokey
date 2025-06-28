#pragma once

#include <cstdint>

enum class PokeyRegister : uint8_t {
    AUDF1   = 0x00, // Audio Frequency Channel 1
    AUDC1   = 0x01, // Audio Control Channel 1
    AUDF2   = 0x02, // Audio Frequency Channel 2
    AUDC2   = 0x03, // Audio Control Channel 2
    AUDF3   = 0x04, // Audio Frequency Channel 3
    AUDC3   = 0x05, // Audio Control Channel 3
    AUDF4   = 0x06, // Audio Frequency Channel 4
    AUDC4   = 0x07, // Audio Control Channel 4
    AUDCTL  = 0x08, // Audio Control (global)
    STIMER  = 0x09, // Reset timers
    SKRES   = 0x0A, // Reset SKSTAT flags
    POTGO   = 0x0B, // Start POT scan
    SEROUT  = 0x0D, // Serial output data
    IRQEN   = 0x0E, // Interrupt enable
    SKCTL   = 0x0F  // Serial/Keyboard control

};

constexpr uint8_t addr(PokeyRegister r) { return static_cast<uint8_t>(r); }
