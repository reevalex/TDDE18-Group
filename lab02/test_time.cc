#include "catch_amalgamated.hpp"
#include "time.h"
#include <sstream>

using namespace std;

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

TEST_CASE("Converting time to string: is_string()")
{
    SECTION("24-hour format (default)")
    {
        CHECK(to_string(Time{1, 2, 3}) == "01:02:03");
        CHECK(to_string(Time{13, 2, 3}) == "13:02:03");
    }

    SECTION("12-hour format (am/pm)")
    {
        CHECK(to_string(Time{1, 2, 3}, true) == "01:02:03 am");
        CHECK(to_string(Time{13, 2, 3}, true) == "01:02:03 pm");
    }
}

TEST_CASE("Checking if time is before noon: is_am()")

{
    SECTION("Midnight to before noon (am times)")
    {
        CHECK(is_am(Time{00, 00, 00}));
        CHECK(is_am(Time{11, 59, 59}));
    }

    SECTION("Noon to before midnight (pm times)")
    {
        CHECK_FALSE(is_am(Time{12, 00, 00}));
        CHECK_FALSE(is_am(Time{23, 59, 59}));
    }
}

TEST_CASE("Adding seconds to time: operator+")
{
    SECTION("Additions without overflow")
    {
        Time t{10, 20, 30};
        Time result = t + 5;
        CHECK(to_string(result) == "10:20:35");
        CHECK(to_string(t) == "10:20:30");
    }

    SECTION("Seconds overflow to minutes")
    {
        Time t{10, 20, 55};
        Time result = t + 10;
        CHECK(to_string(result) == "10:21:05");
    }

    SECTION("Seconds overflow to hour")
    {
        Time t{10, 59, 55};
        Time result = t + 10;
        CHECK(to_string(result) == "11:00:05");
    }

    SECTION("Commutative addition: int + time")
    {
        Time t{10, 20, 30};
        Time result1 = t + 5;
        Time result2 = 5 + t;
        CHECK(to_string(result1) == to_string(result2));
    }
}

TEST_CASE("Subtracting seconds to time: operator-")
{
    SECTION("Subtraction without overflow")
    {
        Time t{10, 20, 30};
        Time result = t - 5;
        CHECK(to_string(result) == "10:20:25");
        CHECK(to_string(t) == "10:20:30");
    }

    SECTION("Seconds underflow to prev minutes")
    {
        Time t{10, 20, 05};
        Time result = t - 10;
        CHECK(to_string(result) == "10:19:55");
    }

    SECTION("Seconds underflow to prev hour")
    {
        Time t{10, 00, 05};
        Time result = t - 10;
        CHECK(to_string(result) == "09:59:55");
    }
}

TEST_CASE("Increment: ++ prefix and postfix")
{
    SECTION("Prefix increment (++t)")
    {
        Time t{10, 20, 30};
        Time result = ++t; // increment first then assign to result
        CHECK(to_string(t) == "10:20:31");
        CHECK(result == Time{10, 20, 31});
    }

    SECTION("Postfix increment (t++)")
    {
        Time t{10, 20, 30};
        Time result = t++; // assign t to result then increment
        CHECK(to_string(t) == "10:20:31");
        CHECK(result == Time{10, 20, 30});
        cout << to_string(result) << endl;
    }
}

TEST_CASE("Decrement: -- prefix and postfix")
{

    SECTION("Prefix decrement (--t)")
    {
        Time t{10, 20, 30};
        Time result = --t; // decrement first then assign to result
        CHECK(to_string(t) == "10:20:29");
        CHECK(result == Time{10, 20, 29});
    }

    SECTION("Postfix decrement (t--)")
    {
        Time t{10, 20, 30};
        Time result = t--; // assign t to result then decrement
        CHECK(to_string(t) == "10:20:29");
        CHECK(result == Time{10, 20, 30});
        cout << to_string(result) << endl;
    }
}

TEST_CASE("Comparison operators")
{
    SECTION("Equality: ==")
    {
        // Same times should be equal
        CHECK(Time{10, 20, 30} == Time{10, 20, 30});
        CHECK(Time{0, 0, 0} == Time{0, 0, 0});
        CHECK(Time{23, 59, 59} == Time{23, 59, 59});

        // Different times should not be equal
        CHECK_FALSE(Time{10, 20, 30} == Time{10, 20, 31}); // Different second
        CHECK_FALSE(Time{10, 20, 30} == Time{10, 21, 30}); // Different minute
        CHECK_FALSE(Time{10, 20, 30} == Time{11, 20, 30}); // Different hour
    }

    SECTION("Inequality: !=")
    {
        // Different times should be not-equal
        CHECK(Time{10, 20, 30} != Time{10, 20, 31});
        CHECK(Time{10, 20, 30} != Time{10, 21, 30});
        CHECK(Time{10, 20, 30} != Time{11, 20, 30});

        // Same times should not be not-equal (double negative = positive)
        CHECK_FALSE(Time{10, 20, 30} != Time{10, 20, 30});
        CHECK_FALSE(Time{0, 0, 0} != Time{0, 0, 0});
    }

    SECTION("Less than: <")
    {
        // Earlier times are less than later times
        CHECK(Time{10, 20, 30} < Time{10, 20, 31}); // One second later
        CHECK(Time{10, 20, 30} < Time{10, 21, 30}); // One minute later
        CHECK(Time{10, 20, 30} < Time{11, 20, 30}); // One hour later
        CHECK(Time{0, 0, 0} < Time{23, 59, 59});    // Midnight < end of day

        // Same time is not less than itself
        CHECK_FALSE(Time{10, 20, 30} < Time{10, 20, 30});

        // Later times are not less than earlier times
        CHECK_FALSE(Time{10, 20, 31} < Time{10, 20, 30});
        CHECK_FALSE(Time{23, 59, 59} < Time{0, 0, 0});
    }

    SECTION("Less than or equal: <=")
    {
        // Earlier times are <= later times
        CHECK(Time{10, 20, 30} <= Time{10, 20, 31});
        CHECK(Time{10, 20, 30} <= Time{11, 20, 30});

        // Same times are <= each other
        CHECK(Time{10, 20, 30} <= Time{10, 20, 30});
        CHECK(Time{0, 0, 0} <= Time{0, 0, 0});

        // Later times are not <= earlier times
        CHECK_FALSE(Time{10, 20, 31} <= Time{10, 20, 30});
    }

    SECTION("Greater than: >")
    {
        // Later times are greater than earlier times
        CHECK(Time{10, 20, 31} > Time{10, 20, 30});
        CHECK(Time{10, 21, 30} > Time{10, 20, 30});
        CHECK(Time{11, 20, 30} > Time{10, 20, 30});
        CHECK(Time{23, 59, 59} > Time{0, 0, 0});

        // Same time is not greater than itself
        CHECK_FALSE(Time{10, 20, 30} > Time{10, 20, 30});

        // Earlier times are not greater than later times
        CHECK_FALSE(Time{10, 20, 30} > Time{10, 20, 31});
    }

    SECTION("Greater than or equal: >=")
    {
        // Later times are >= earlier times
        CHECK(Time{10, 20, 31} >= Time{10, 20, 30});
        CHECK(Time{11, 20, 30} >= Time{10, 20, 30});

        // Same times are >= each other
        CHECK(Time{10, 20, 30} >= Time{10, 20, 30});
        CHECK(Time{23, 59, 59} >= Time{23, 59, 59});

        // Earlier times are not >= later times
        CHECK_FALSE(Time{10, 20, 30} >= Time{10, 20, 31});
    }
}

TEST_CASE("Stream input: >>")
{
    SECTION("Valid input formats")
    {
        istringstream iss("10 20 30");
        Time t{};
        iss >> t;
        CHECK_FALSE(iss.fail());
        CHECK(to_string(t) == "10:20:30");
    }

    SECTION("Invalid formats - should set fail bit")
    {
        Time t{12, 34, 56};
        istringstream iss;

        // Wrong separator
        iss.clear();
        iss.str("10-20-30");
        iss >> t;
        CHECK(iss.fail());
        CHECK(to_string(t) == "12:34:56");

        // Not numbers
        iss.clear();
        iss.str("ab:cd:ef");
        iss >> t;
        CHECK(iss.fail());
        CHECK(to_string(t) == "12:34:56");
    }

    SECTION("Invalid values - should set fail bit")
    {
        Time t{12, 34, 56};
        istringstream iss;

        // Hour too large
        iss.str("24:00:00");
        iss >> t;
        CHECK(iss.fail());
        CHECK(to_string(t) == "12:34:56");

        // Negative values
        iss.clear();
        iss.str("-1:20:30");
        iss >> t;
        CHECK(iss.fail());
        CHECK(to_string(t) == "12:34:56");
    }
}

TEST_CASE("Stream output: <<")
{
    SECTION("Basic output formatting")
    {
        ostringstream oss;

        Time t1{9, 5, 3};
        oss << t1;
        CHECK(oss.str() == "09:05:03");

        oss.str(""); // Clear the stream
        Time t2{23, 59, 59};
        oss << t2;
        CHECK(oss.str() == "23:59:59");

        oss.str("");
        Time t3{0, 0, 0};
        oss << t3;
        CHECK(oss.str() == "00:00:00");
    }

    SECTION("Multiple outputs to same stream")
    {
        ostringstream oss;
        Time t1{10, 20, 30};
        Time t2{11, 21, 31};

        oss << t1 << " and " << t2;
        CHECK(oss.str() == "10:20:30 and 11:21:31");
    }
}
