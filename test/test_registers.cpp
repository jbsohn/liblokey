#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "lokey.hpp"

TEST_CASE("Basic register write") {
    const Lokey lokey(44100, 1);
    lokey.writeRegister(0x0F, 0xAA);
    CHECK(true); // Replace with real state check once implemented
}