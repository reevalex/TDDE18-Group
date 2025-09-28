#include "time.h"
#include <sstream>
#include <iomanip>

#include "time.h" // header guards sanity check

using namespace std;

int time_to_seconds(Time const &t)
{
    return t.hour * 3600 + t.minute * 60 + t.second;
}

Time seconds_to_time(int total_seconds)
{
    while (total_seconds < 0)
    {
        total_seconds += 86400;
    }

    total_seconds %= 86400; // Ensure to stay within 24h period

    Time result;
    result.hour = total_seconds / 3600; // How many whole hours
    total_seconds %= 3600;              // Remove the hours from total
    result.minute = total_seconds / 60; // How many whole minutes
    result.second = total_seconds % 60; // What's left in seconds

    return result;
}

Time operator+(Time const &t, int seconds)
{
    int total_seconds{time_to_seconds(t) + seconds};
    return seconds_to_time(total_seconds);
}

Time operator+(int seconds, Time const &t)
{
    return t + seconds; // Reuse operator+
}

Time operator-(Time const &t, int seconds)
{
    int total_seconds{time_to_seconds(t) - seconds};
    return seconds_to_time(total_seconds);
}

Time operator++(Time &t)
{
    t = t + 1;
    return t;
}

Time operator++(Time &t, int)
{
    Time result = t;
    ++t;
    return result;
}

Time operator--(Time &t)
{
    t = t - 1;
    return t;
}

Time operator--(Time &t, int)
{
    Time result = t;
    --t;
    return result;
}

bool operator==(Time const &lhs, Time const &rhs)
{
    return lhs.hour == rhs.hour &&
           lhs.minute == rhs.minute &&
           lhs.second == rhs.second;
}

bool operator!=(Time const &lhs, Time const &rhs)
{
    return !(lhs == rhs); // Reuse equality (==)
}

bool operator<(Time const &lhs, Time const &rhs)
{
    return time_to_seconds(lhs) < time_to_seconds(rhs);
}

bool operator<=(Time const &lhs, Time const &rhs)
{
    return (lhs < rhs) || (lhs == rhs); // Reuse equality (==) and less than (<)
}

bool operator>(Time const &lhs, Time const &rhs)
{
    return !(lhs <= rhs); // Reuse less than or equal (<=)
}

bool operator>=(Time const &lhs, Time const &rhs)
{
    return !(lhs < rhs); // Reuse less than(<)
}

ostream &operator<<(ostream &os, Time const &t)
{
    os << to_string(t); // HH:MM:SS format
    return os;
}

istream &operator>>(istream &is, Time &t)
{
    int hour, minute, second;
    char c1, c2;

    if (!(is >> hour >> c1 >> minute >> c2 >> second) || c1 != ':' || c2 != ':')
    {
        is.setstate(ios::failbit);
        return is;
    }

    Time t_temp{hour, minute, second};

    if (!is_valid(t_temp))
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

    if (!format_12) // default 24-h format
    {
        oss << setfill('0') << setw(2) << t.hour << ":"
            << setfill('0') << setw(2) << t.minute << ":"
            << setfill('0') << setw(2) << t.second;
    }
    else
    {
        int hour;
        string period;

        if (is_am(t))
        {
            if (t.hour == 0)
            {
                hour = 12;
            }
            else
            {
                hour = t.hour;
            }
            period = " am";
        }
        else
        {
            if (t.hour == 12)
            {
                hour = 12;
            }
            else
            {
                hour = t.hour - 12;
            }
            period = " pm";
        }

        oss << setfill('0') << setw(2) << hour << ":"
            << setfill('0') << setw(2) << t.minute << ":"
            << setfill('0') << setw(2) << t.second << period;
    }

    return oss.str();
}

// int main()
// {
//     return 0;
// }
