#include "LoadingUtils.h"

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

bool LoadingUtils::loadCappedNormalized(const int VALUE, double& out, const int MIN, int MAX)
{
    if (VALUE < MIN || VALUE > MAX)
    {
        out = 0;
        return false;
    }
    else
    {
        out = (double)VALUE / MAX;
        return true;
    }
}
