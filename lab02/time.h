#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>
using namespace std;

struct Time
{
    int hour;
    int minute;
    int second;

    Time &operator++();
    Time operator++(int);

    Time &operator--();
    Time operator--(int);
};

Time operator+(Time const &t, int seconds); // Time + Seconds
Time operator+(int seconds, Time const &t); // Seconds + Time

Time operator-(Time const &t, int seconds); // Time - seconds

bool operator==(Time const &lhs, Time const &rhs);
bool operator!=(Time const &lhs, Time const &rhs);
bool operator<(Time const &lhs, Time const &rhs);
bool operator<=(Time const &lhs, Time const &rhs);
bool operator>(Time const &lhs, Time const &rhs);
bool operator>=(Time const &lhs, Time const &rhs);

ostream &operator<<(ostream &os, Time const &t);
istream &operator>>(istream &is, Time &t);

bool is_valid(Time const &t);
bool is_am(Time const &t);
string to_string(Time const &t, bool format_12h = false);

#endif