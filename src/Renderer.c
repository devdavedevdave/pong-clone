#include "Renderer.h"
#include <complex.h>

// MEMORY
void *Renderer_init() {

  Renderer *renderer = malloc(sizeof(Renderer));
  if (renderer == NULL) {
    printf("Failed to allocate memory for Renderer\n");
  }

  renderer->window = NULL;
  renderer->renderer = NULL;
  renderer->font = NULL;

  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
  }

  SDL_Window *window = NULL;

  // Create a window with the specified position, dimensions, and flags
  window = SDL_CreateWindow(
      "SDL Pong",             // window title
      SDL_WINDOWPOS_CENTERED, // initial x position
      SDL_WINDOWPOS_CENTERED, // initial y position
      760,             // width, in pixels // TODO: Import via global config
      760,             // height, in pixels
      SDL_WINDOW_SHOWN // flags - see below
  );

  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    SDL_Quit();
  }

  renderer->window = window;

  SDL_Renderer *sdlRenderer = NULL;

  // Create a renderer for our window, using hardware acceleration and vsync
  sdlRenderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (sdlRenderer == NULL) {
    printf("Could not create renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  renderer->renderer = sdlRenderer;

  // Create Typography instance
  if (TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
  }

  // Loads font
  TTF_Font *font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 64);
  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }

  renderer->font = font;

  return renderer;
}

void Renderer_destroy(Renderer *renderer) {
  if (renderer) {
    free(renderer->window);
    free(renderer->renderer);
    free(renderer);
  }
}
