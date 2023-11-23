#include "Utils.h"

int clamp(const int value, const int min, const int max)
{
    const int IS_SMALLER = value < min;
    const int IS_LARGER = value > max;

    return IS_SMALLER ? min : (IS_LARGER ? max : value);
}