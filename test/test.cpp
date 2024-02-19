#include <catch2/catch_test_macros.hpp>

TEST_CASE("Testing framework", "[TEST]") {
    volatile int x = 1;
    REQUIRE(x == 1);
}