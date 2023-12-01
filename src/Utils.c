#include <SDL.h>
#include "Utils.h"

Borders evaluateRectBorder(SDL_Rect *rect)
{
    Borders borders;
    borders.top = rect->y;
    borders.bottom = rect->y + rect->h;
    borders.left = rect->x;
    borders.right = rect->x + rect->w;

    return borders;
}

int clamp(const int value, const int min, const int max)
{
    const int IS_SMALLER = value < min;
    const int IS_LARGER = value > max;

    return IS_SMALLER ? min : (IS_LARGER ? max : value);
}