// This test program uses a test framework supporting TDD and BDD.
// You are not required to use the framework, but encouraged to.
// Code:
// https://github.com/catchorg/Catch2
// Documentation:
// https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

// You ARE however required to implement all test cases outlined here,
// even if you do it by way of your own function for each case.  You
// are recommended to solve the cases in order, and rerun all tests
// after you modify your code.

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "list.h"
#include <sstream>
#include <iostream>

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE("Create an empty list")
{
    Sorted_List l;

    REQUIRE(l.size() == 0);
    REQUIRE_THROWS_AS(l.at(0), std::out_of_range);
}

TEST_CASE("Insert single element")
{
    Sorted_List l;

    l.insert(5);
    REQUIRE(l.size() == 1);
    REQUIRE(l.at(0) == 5);
}

TEST_CASE("Insertion with multiple elements")
{
    Sorted_List l;
    for (int v : {5, 3, 9, 7})
    {
        l.insert(v);
    }

    REQUIRE(l.size() == 4);
    REQUIRE(l.at(0) == 3);
    REQUIRE(l.at(1) == 5);
    REQUIRE(l.at(2) == 7);
    REQUIRE(l.at(3) == 9);
}

TEST_CASE("Remove elements")
{
    Sorted_List l;
    for (int v : {5, 3, 9, 7})
    {
        l.insert(v);
    }

    REQUIRE(l.remove(3)); // head
    REQUIRE(l.remove(7)); // middle
    REQUIRE(l.remove(9)); // tail
    REQUIRE_FALSE(l.remove(4));
    REQUIRE(l.size() == 1);
    REQUIRE(l.at(0) == 5);
}

TEST_CASE("Copy Constructor")
{
    Sorted_List l1;
    for (int v : {5, 3, 9, 7})
    {
        l1.insert(v);
    }

    Sorted_List l2 = l1; // copy
    l2.insert(4);

    // l1 = 3 5 7 9
    // l2 = 3 4 5 7 9

    REQUIRE(l1.size() == 4);
    REQUIRE(l2.size() == 5);
    REQUIRE(l1.at(1) == 5);
    REQUIRE(l2.at(1) == 4);
}

TEST_CASE("Copy Assignment")
{
    Sorted_List l1;
    for (int v : {5, 3, 9, 7})
    {
        l1.insert(v);
    }

    Sorted_List l2;
    for (int v : {2, 4, 6})
    {
        l2.insert(v);
    }

    l2 = l1;
    l2.insert(8);
    REQUIRE(l1.size() == 4);
    REQUIRE(l2.size() == 5);
}

TEST_CASE("Move Constructor & Move Assignment")
{
    Sorted_List l1;
    for (int v : {5, 3, 9, 7})
    {
        l1.insert(v);
    }

    Sorted_List l2 = std::move(l1); // move constructor
    REQUIRE(l1.size() == 0);
    REQUIRE(l2.size() == 4);

    Sorted_List l3;
    l3.insert(1);
    l3 = std::move(l2); // move assignment
    REQUIRE(l2.size() == 0);
    REQUIRE(l3.size() == 4);
}

TEST_CASE("Print in order using recursion")
{
    Sorted_List l;
    for (int v : {5, 3, 9, 7})
    {
        l.insert(v);
    }

    std::ostringstream oss;
    auto *old = std::cout.rdbuf(oss.rdbuf());
    l.print();
    std::cout.rdbuf(old);
    REQUIRE(oss.str() == "3 5 7 9\n");
}

// It is your job to create new test cases and fully test your Sorted_List class