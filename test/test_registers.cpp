#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "lokey.hpp"

TEST_CASE("Basic register write") {
    Lokey lokey(44100, 1);
    CHECK(true);  // Replace with real state check once implemented
}