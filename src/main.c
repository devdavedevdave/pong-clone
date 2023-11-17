#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"

int main(int argc, char *argv[])
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;

    // Create a window with the specified position, dimensions, and flags
    window = SDL_CreateWindow(
        "SDL Pong",             // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        760,                    // width, in pixels
        760,                    // height, in pixels
        SDL_WINDOW_SHOWN        // flags - see below
    );

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = NULL;

    // Create a renderer for our window, using hardware acceleration and vsync
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;

    SDL_Rect ball = {365, 365, 20, 20};
    Ball gameBall = {&ball, 1, 1, 2};

    SDL_Rect paddle = {365, 365, 20, 20};
    Paddle gamePaddle = {&paddle, 2};

    SDL_Rect middleLine = {365, 0, 10, 5};

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            // Additional event handling
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Game logic and render updates go here
        // For example, drawing a white rectangle (like a pong paddleLeft)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white

        handleCollision(&gameBall, &gamePaddle);
        setDirections(&gameBall);

        SDL_RenderFillRect(renderer, &ball);

        int drawLine = 1;
        while (drawLine)
        {
            SDL_RenderFillRect(renderer, &middleLine);
            middleLine.y += 10;

            if (middleLine.y > 760 - middleLine.h)
            {
                drawLine = 0;
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        middleLine.y = 0;
        SDL_Delay(16); // Approximately 60 frames per second (1000ms/60 ≈ 16ms per frame)
    }

    // Clean up before exiting
    SDL_Quit();
    return 0;
}
