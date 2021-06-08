#include "LoadingUtils.h"

bool LoadingUtils::loadNotZero(const int VALUE, int& out)
{
    if (VALUE == 0)
    {
        out = 0;
        return false;
    }
    else
    {
        out = VALUE;
        return true;
    }
}

bool LoadingUtils::loadCapped(const int VALUE, int& out, const int MIN, int MAX)
{
    if (VALUE < MIN || VALUE > MAX)
    {
        out = 0;
        return false;
    }
    else
    {
        out = VALUE;
        return true;
    }
}

bool LoadingUtils::loadCappedMaxNormalized(const int VALUE, double& out, const int MAX)
{
    if (VALUE < 0 || VALUE > MAX)
    {
        out = 0;
        return false;
    }
    else
    {
        out = double(VALUE) / MAX;
        return true;
    }
}

bool LoadingUtils::loadCappedMinMaxNormalized(const int VALUE, double& out, const int MIN, int MAX)
{
    if (VALUE < MIN || VALUE > MAX)
    {
        out = 0;
        return false;
    }
    else
    {
        const double DELTA = 2.f / (MAX - MIN);
        out = (double(VALUE) - MIN) * DELTA - 1;
        return true;
    }
}
