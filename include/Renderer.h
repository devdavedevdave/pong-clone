#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} Renderer;

// MEMORY
void *Renderer_init();

void Renderer_destroy(Renderer *renderer);

#endif // RENDERER_H
