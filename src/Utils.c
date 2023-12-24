#include <SDL.h>
#include "Utils.h"
#include "Ball.h"

Borders evaluateRectBorder(SDL_Rect *rect)
{
    Borders borders;
    borders.top = rect->y;
    borders.bottom = rect->y + rect->h;
    borders.left = rect->x;
    borders.right = rect->x + rect->w;

    return borders;
}

int isColliding(Borders *a, Borders *b, CollisionType type)
{
    if (type == COLLIDE_LEFT)
    {
        return a->left <= b->right && a->bottom >= b->top && a->top <= b->bottom;
    }
    else
    {
        return a->right >= b->left && a->bottom >= b->top && a->top <= b->bottom;
    }
}

int clamp(const int value, const int min, const int max)
{
    const int IS_SMALLER = value < min;
    const int IS_LARGER = value > max;

    return IS_SMALLER ? min : (IS_LARGER ? max : value);
}

void drawMiddleLine(SDL_Rect *middleLine, SDL_Renderer *renderer)
{
    int drawLine = 1;
    while (drawLine)
    {
        SDL_RenderFillRect(renderer, middleLine);
        middleLine->y += 10;

        if (middleLine->y > SCREEN_HEIGHT - middleLine->h)
        {
            drawLine = 0;
        }
    }
}

// MEMORY
void *MiddleLine_init()
{
    SDL_Rect *middleLine = malloc(sizeof(SDL_Rect));
    if (!middleLine)
    {
        return NULL;
    }

    *(middleLine) = (SDL_Rect){365, 0, 10, 5};

    return middleLine;
}

void MiddleLine_destroy(SDL_Rect *middleLine)
{
    if (middleLine)
    {
        free(middleLine);
    }
}
