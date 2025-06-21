#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "lokey.h"

TEST_CASE("Basic register write") {
    lokey_init(44100, 1);
    lokey_write_register(0x0F, 0xAA);
    CHECK(true); // Replace with real state check once implemented
}