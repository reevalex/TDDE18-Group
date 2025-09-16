#include "time.h"

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