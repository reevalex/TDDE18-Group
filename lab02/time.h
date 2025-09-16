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
};

bool is_valid(Time const &t);

#endif