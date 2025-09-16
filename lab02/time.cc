#include "time.h"
#include <sstream>
#include <iomanip>

Time operator+(Time const &t, int seconds)
{
    int total_seconds = t.hour * 3600 + t.minute * 60 + t.second;
    total_seconds += seconds;

    total_seconds %= 86400; // Ensure to stay within 24h period

    Time result;
    result.hour = total_seconds / 3600; // How many whole hours
    total_seconds %= 3600;              // Remove the hours from total
    result.minute = total_seconds / 60; // How many whole minutes
    result.second = total_seconds % 60; // What's left in seconds

    return result;
}

Time operator+(int seconds, Time const &t)
{
    return t + seconds; // Reuse operator+ by swapping order
}

Time operator-(Time const &t, int seconds)
{
    int total_seconds = t.hour * 3600 + t.minute * 60 + t.second;
    total_seconds -= seconds;

    total_seconds %= 86400; // Ensure to stay within 24h period

    Time result;
    result.hour = total_seconds / 3600; // How many whole hours
    total_seconds %= 3600;              // Remove the hours from total
    result.minute = total_seconds / 60; // How many whole minutes
    result.second = total_seconds % 60; // What's left in seconds

    return result;
}

Time &Time::operator++()
{
    *this = *this + 1;
    return *this;
}

Time Time::operator++(int)
{
    Time old_value = *this;
    ++(*this);
    return old_value;
}

Time &Time::operator--()
{
    *this = *this - 1;
    return *this;
}

Time Time::operator--(int)
{
    Time old_value = *this;
    --(*this);
    return old_value;
}

bool operator==(Time const &lhs, Time const &rhs)
{
    return lhs.hour == rhs.hour &&
           lhs.minute == rhs.minute &&
           lhs.second == rhs.second;
}

bool operator!=(Time const &lhs, Time const &rhs)
{
    return !(lhs == rhs);
}

bool operator<(Time const &lhs, Time const &rhs)
{
    if (lhs.hour < rhs.hour)
    {
        return true;
    }
    if (lhs.hour > rhs.hour)
    {
        return false;
    }

    if (lhs.minute < rhs.minute)
    {
        return true;
    }
    if (lhs.minute > rhs.minute)
    {
        return false;
    }

    return lhs.second < rhs.second;
}

bool operator<=(Time const &lhs, Time const &rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(Time const &lhs, Time const &rhs)
{
    return !(lhs <= rhs);
}

bool operator>=(Time const &lhs, Time const &rhs)
{
    return !(lhs < rhs);
}

ostream &operator<<(ostream &os, Time const &t)
{
    os << to_string(t);
    return os;
}

istream &operator>>(istream &is, Time &t)
{
    int hour, minute, second;
    char c1, c2;

    is >> hour >> c1 >> minute >> c2 >> second;

    if (is.fail() || c1 != ':' || c2 != ':')
    {
        is.setstate(ios::failbit);
        return is;
    }

    Time t_temp{hour, minute, second};

    if (!is_valid(t))
    {
        is.setstate(ios::failbit);
        return is;
    }

    t = t_temp;

    return is;
}

bool is_valid(Time const &t)
{
    if (t.hour < 0 || t.hour > 23)
    {
        return false;
    }

    if (t.minute < 0 || t.minute > 59)
    {
        return false;
    }

    if (t.second < 0 || t.second > 59)
    {
        return false;
    }

    return true;
}

bool is_am(Time const &t)
{
    return t.hour < 12;
}

string to_string(Time const &t, bool format_12)
{
    ostringstream oss;

    if (!format_12)
    {
        oss << setfill('0') << setw(2) << t.hour << ":"
            << setfill('0') << setw(2) << t.minute << ":"
            << setfill('0') << setw(2) << t.second;
    }
    else
    {
        int hour;
        string period;

        if (t.hour == 0)
        {
            hour = 12;
            period = " am";
        }
        else if (t.hour < 12)
        {
            hour = t.hour;
            period = " am";
        }
        else if (t.hour == 12)
        {
            hour = t.hour;
            period = " pm";
        }
        else
        {
            hour = t.hour - 12;
            period = " pm";
        }
        oss << setfill('0') << setw(2) << hour << ":"
            << setfill('0') << setw(2) << t.minute << ":"
            << setfill('0') << setw(2) << t.second << period;
    }

    return oss.str();
}