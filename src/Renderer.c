#include <SDL.h>
#include "Renderer.h"
#include "Game.h"

Renderer *Renderer_init()
{

    Renderer *renderer = malloc(sizeof(Renderer));
    if (renderer == NULL)
    {
        printf("Failed to allocate memory for Renderer\n");
        return NULL;
    }

    renderer->window = NULL;
    renderer->renderer = NULL;

    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = NULL;

    // Create a window with the specified position, dimensions, and flags
    window = SDL_CreateWindow(
        "SDL Pong",             // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        SCREEN_WIDTH,           // width, in pixels
        SCREEN_HEIGHT,          // height, in pixels
        SDL_WINDOW_SHOWN        // flags - see below
    );

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    renderer->window = window;

    SDL_Renderer *sdlRenderer = NULL;

    // Create a renderer for our window, using hardware acceleration and vsync
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == NULL)
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    renderer->renderer = sdlRenderer;
    return renderer;
}

void Renderer_destroy(Renderer *renderer)
{
    if (renderer)
    {
        free(renderer->window);
        free(renderer->renderer);
        free(renderer);
    }
}