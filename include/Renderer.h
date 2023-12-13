#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} Renderer;

Renderer *Renderer_init();

void Renderer_destroy(Renderer *renderer);

void prepareFrameForRendering();

void drawGameElements();

#endif // RENDERER_H