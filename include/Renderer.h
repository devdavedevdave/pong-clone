#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
} Renderer;

// MEMORY
void *Renderer_init();

void Renderer_destroy(Renderer *renderer);

#endif // RENDERER_H
