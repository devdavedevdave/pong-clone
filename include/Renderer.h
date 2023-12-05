#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} Renderer;

Renderer *initRenderer();

void prepareFrameForRendering();

void drawGameElements();

#endif // RENDERER_H