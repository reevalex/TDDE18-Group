#include "catch_amalgamated.hpp"
#include "time.h"
#include <sstream>

TEST_CASE("Time struct construction")
{
    Time t{11, 22, 33};

    CHECK(t.hour == 11);
    CHECK(t.minute == 22);
    CHECK(t.second == 33);
}

TEST_CASE("Checking time validity: is_valid()")
{
    SECTION("Valid times")
    {
        CHECK(is_valid(Time{0, 0, 0}));
    }

    SECTION("Invalid times: hours")
    {
        CHECK_FALSE(is_valid(Time{24, 0, 0}));
    }

    SECTION("Invalid times: minutes")
    {
        CHECK_FALSE(is_valid(Time{0, 60, 0}));
    }

    SECTION("Invalid times: seconds")
    {
        CHECK_FALSE(is_valid(Time{0, 0, 60}));
    }
}