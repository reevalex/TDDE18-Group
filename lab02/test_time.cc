#include "catch_amalgamated.hpp"
#include "time.h"
#include <sstream>

using namespace std;

TEST_CASE("Time struct construction")
{
    Time t{1, 2, 3};

    CHECK(t.hour == 1);
    CHECK(t.minute == 2);
    CHECK(t.second == 3);
}

TEST_CASE("Checking time validity: is_valid()")
{
    SECTION("Valid times - boundary values")
    {
        CHECK(is_valid(Time{0, 0, 0}));  // Midnight
        CHECK(is_valid(Time{12, 0, 0})); // Noon
        CHECK(is_valid(Time{23, 0, 0})); // Max valid hour
        CHECK(is_valid(Time{0, 59, 0})); // Max valid minute
        CHECK(is_valid(Time{0, 0, 59})); // Max valid second
    }

    SECTION("Invalid times: hours")
    {
        CHECK_FALSE(is_valid(Time{24, 0, 0})); // Hour too large
        CHECK_FALSE(is_valid(Time{-1, 0, 0})); // Negative hour
    }

    SECTION("Invalid times: minutes")
    {
        CHECK_FALSE(is_valid(Time{0, 60, 0}));   // Minute too large
        CHECK_FALSE(is_valid(Time{12, -1, 30})); // Negative minute
    }

    SECTION("Invalid times: seconds")
    {
        CHECK_FALSE(is_valid(Time{0, 0, 60}));   // Second too large
        CHECK_FALSE(is_valid(Time{15, 30, -1})); // Negative second
    }

    SECTION("Invalid times: multiple invalid arguments")
    {
        CHECK_FALSE(is_valid(Time{24, 60, 60})); // All too large
        CHECK_FALSE(is_valid(Time{-1, -1, -1})); // All negative
    }
}

TEST_CASE("Converting time to string: to_string()")
{
    SECTION("24-hour format (default)")
    {
        CHECK(to_string(Time{1, 2, 3}) == "01:02:03");
        CHECK(to_string(Time{13, 2, 3}) == "13:02:03");
        CHECK(to_string(Time{0, 0, 0}) == "00:00:00");  // Midnight
        CHECK(to_string(Time{12, 0, 0}) == "12:00:00"); // Noon
    }

    SECTION("12-hour format (am/pm)")
    {
        CHECK(to_string(Time{0, 0, 0}, true) == "12:00:00 am"); // Midnight -> 12 am
        CHECK(to_string(Time{1, 2, 3}, true) == "01:02:03 am");
        CHECK(to_string(Time{11, 59, 59}, true) == "11:59:59 am");
        CHECK(to_string(Time{12, 0, 0}, true) == "12:00:00 pm"); // Noon -> 12 pm
        CHECK(to_string(Time{12, 30, 45}, true) == "12:30:45 pm");
        CHECK(to_string(Time{13, 2, 3}, true) == "01:02:03 pm");
        CHECK(to_string(Time{23, 59, 59}, true) == "11:59:59 pm");
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

    SECTION("Day overflow - wraps around to next day")
    {
        Time t1{23, 59, 59};
        Time result1 = t1 + 1;
        CHECK(to_string(result1) == "00:00:00");

        Time t2{23, 30, 45};
        Time result2 = t2 + 3600; // Add 1 hour
        CHECK(to_string(result2) == "00:30:45");
    }

    SECTION("Add day")
    {
        Time t{12, 0, 0};
        Time result = t + 86400; // Add 24 hours
        CHECK(to_string(result) == "12:00:00");
    }

    SECTION("Zero addition")
    {
        Time t{15, 30, 45};
        Time result = t + 0;
        CHECK(to_string(result) == "15:30:45");
        CHECK(result == t);
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

    SECTION("Day underflow - wraps to previous day")
    {
        Time t1{0, 0, 0};
        Time result1 = t1 - 1;
        CHECK(to_string(result1) == "23:59:59");

        Time t2{23, 30, 45};
        Time result2 = t2 - 3600; // Subtract 1 hour
        CHECK(to_string(result2) == "22:30:45");
    }

    SECTION("Subtract day")
    {
        Time t{12, 0, 0};
        Time result = t - 86400; // Subtract 24 hours
        CHECK(to_string(result) == "12:00:00");
    }

    SECTION("Zero subtraction")
    {
        Time t{15, 30, 45};
        Time result = t - 0;
        CHECK(to_string(result) == "15:30:45");
        CHECK(result == t);
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

    SECTION("Increment at day boundary")
    {
        Time t1{23, 59, 59};
        ++t1;
        CHECK(to_string(t1) == "00:00:00");

        Time t2{23, 59, 59};
        Time old = t2++;
        CHECK(to_string(t2) == "00:00:00");
        CHECK(to_string(old) == "23:59:59");
    }

    SECTION("Increment across boundaries")
    {
        Time t1{10, 30, 59};
        ++t1;
        CHECK(to_string(t1) == "10:31:00");

        Time t2{10, 59, 59};
        ++t2;
        CHECK(to_string(t2) == "11:00:00");
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

    SECTION("Decrement at day boundary")
    {
        Time t1{0, 0, 0};
        --t1;
        CHECK(to_string(t1) == "23:59:59");

        Time t2{0, 0, 0};
        Time old = t2--;
        CHECK(to_string(t2) == "23:59:59");
        CHECK(to_string(old) == "00:00:00");
    }

    SECTION("Decrement across boundaries")
    {
        Time t1{10, 30, 0};
        --t1;
        CHECK(to_string(t1) == "10:29:59");

        Time t2{10, 0, 0};
        --t2;
        CHECK(to_string(t2) == "09:59:59");
    }
}

TEST_CASE("Comparison operators")
{
    SECTION("Equality: ==")
    {
        CHECK(Time{10, 20, 30} == Time{10, 20, 30});
        CHECK(Time{0, 0, 0} == Time{0, 0, 0});
        CHECK(Time{23, 59, 59} == Time{23, 59, 59});

        CHECK_FALSE(Time{10, 20, 30} == Time{10, 20, 31});
        CHECK_FALSE(Time{10, 20, 30} == Time{10, 21, 30});
        CHECK_FALSE(Time{10, 20, 30} == Time{11, 20, 30});
    }

    SECTION("Inequality: !=")
    {
        CHECK(Time{10, 20, 30} != Time{10, 20, 31});
        CHECK(Time{10, 20, 30} != Time{10, 21, 30});
        CHECK(Time{10, 20, 30} != Time{11, 20, 30});
    }

    SECTION("Less than: <")
    {
        CHECK(Time{10, 20, 30} < Time{10, 20, 31});
        CHECK(Time{10, 20, 30} < Time{10, 21, 30});
        CHECK(Time{10, 20, 30} < Time{11, 20, 30});
        CHECK(Time{0, 0, 0} < Time{23, 59, 59});

        CHECK_FALSE(Time{10, 20, 30} < Time{10, 20, 30});
        CHECK_FALSE(Time{10, 20, 31} < Time{10, 20, 30});
    }

    SECTION("Less than or equal: <=")
    {
        CHECK(Time{10, 20, 30} <= Time{10, 20, 31});
        CHECK(Time{10, 20, 30} <= Time{11, 20, 30});
        CHECK(Time{10, 20, 30} <= Time{10, 20, 30});
        CHECK(Time{0, 0, 0} <= Time{0, 0, 0});

        CHECK_FALSE(Time{10, 20, 31} <= Time{10, 20, 30});
    }

    SECTION("Greater than: >")
    {
        CHECK(Time{10, 20, 31} > Time{10, 20, 30});
        CHECK(Time{10, 21, 30} > Time{10, 20, 30});
        CHECK(Time{11, 20, 30} > Time{10, 20, 30});
        CHECK(Time{23, 59, 59} > Time{0, 0, 0});

        CHECK_FALSE(Time{10, 20, 30} > Time{10, 20, 30});
        CHECK_FALSE(Time{10, 20, 30} > Time{10, 20, 31});
    }

    SECTION("Greater than or equal: >=")
    {
        CHECK(Time{10, 20, 31} >= Time{10, 20, 30});
        CHECK(Time{11, 20, 30} >= Time{10, 20, 30});
        CHECK(Time{10, 20, 30} >= Time{10, 20, 30});
        CHECK(Time{23, 59, 59} >= Time{23, 59, 59});

        CHECK_FALSE(Time{10, 20, 30} >= Time{10, 20, 31});
    }
}

TEST_CASE("Stream input: >>")
{
    SECTION("Valid input formats")
    {
        istringstream iss("10:20:30");
        Time t{};
        iss >> t;
        CHECK_FALSE(iss.fail());
        CHECK(to_string(t) == "10:20:30");

        iss.clear(); // Clear stream
        iss.str("00:00:00");
        iss >> t;
        CHECK_FALSE(iss.fail());
        CHECK(to_string(t) == "00:00:00");

        iss.clear();
        iss.str("23:59:59");
        iss >> t;
        CHECK_FALSE(iss.fail());
        CHECK(to_string(t) == "23:59:59");

        iss.clear();
        iss.str("1:2:3");
        iss >> t;
        CHECK_FALSE(iss.fail());
        CHECK(to_string(t) == "01:02:03");
    }

    SECTION("Invalid seperator formats")
    {
        istringstream iss;
        ;
        iss.str("10-20-30");
        Time t1{}; // 1:1:1
        iss >> t1;
        CHECK(iss.fail());

        iss.clear();
        iss.str("10 20 30");
        Time t2{};
        iss >> t2;
        CHECK(iss.fail());

        iss.clear();
        Time t3{};
        iss.str("102030");
        iss >> t3;
        CHECK(iss.fail());

        iss.clear();
        Time t4{};
        iss.str("10:2030");
        iss >> t4;
        CHECK(iss.fail());
    }

    SECTION("Invalid integers")
    {
        istringstream iss;

        Time t1{};
        iss.str("24:00:00");
        iss >> t1;
        CHECK(iss.fail());

        iss.clear();
        Time t2{};
        iss.str("99:30:45");
        iss >> t2;
        CHECK(iss.fail());

        iss.clear();
        Time t3{};
        iss.str("-1:20:30");
        iss >> t3;
        CHECK(iss.fail());

        iss.clear();
        Time t4{};
        iss.str("12:60:30");
        iss >> t4;
        CHECK(iss.fail());

        iss.clear();
        Time t5{};
        iss.str("12:30:60");
        iss >> t5;
        CHECK(iss.fail());

        iss.clear();
        Time t6{};
        iss.str("25:61:61");
        iss >> t6;
        CHECK(iss.fail());
    }

    SECTION("Invalid other cases")
    {
        istringstream iss;

        Time t1{};
        iss.str("ab:cd:ef");
        iss >> t1;
        CHECK(iss.fail());

        iss.clear();
        Time t2{};
        iss.str("12:ab:30");
        iss >> t2;
        CHECK(iss.fail());

        iss.clear();
        Time t3{};
        iss.str("");
        iss >> t3;
        CHECK(iss.fail());

        iss.clear();
        Time t4{};
        iss.str("12:30");
        iss >> t4;
        CHECK(iss.fail());
    }

    SECTION("Input with text")
    {
        istringstream iss;
        Time t{};

        iss.str("10:20:30 extra text");
        iss >> t;
        CHECK_FALSE(iss.fail());
        CHECK(to_string(t) == "10:20:30");

        iss.clear();
        iss.str("time input");
        iss >> t;
        CHECK(iss.fail());
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

        oss.str(""); // Clear stream
        Time t2{23, 59, 59};
        oss << t2;
        CHECK(oss.str() == "23:59:59");

        oss.str("");
        Time t3{0, 0, 0};
        oss << t3;
        CHECK(oss.str() == "00:00:00");
    }
}
