#include <SDL.h>
#include "Game.h"

void drawMiddleLine(SDL_Rect *middleLine, Renderer *renderer)
{
    int drawLine = 1;
    while (drawLine)
    {
        SDL_RenderFillRect(renderer->renderer, middleLine);
        middleLine->y += 10;

        if (middleLine->y > SCREEN_HEIGHT - middleLine->h)
        {
            drawLine = 0;
        }
    }
}