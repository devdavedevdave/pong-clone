#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

typedef struct
{
    int top;
    int bottom;
    int left;
    int right;
} Borders;

Borders evaluateRectBorder(SDL_Rect *rect);

int clamp(const int value, const int min, const int max);

#endif // UTILS_H