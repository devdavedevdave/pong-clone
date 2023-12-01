#include <SDL.h>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Renderer.h"

int main(int argc, char *argv[])
{
    Renderer *renderer = initRenderer();

    int running = 1;

    SDL_Rect ball = {365, 365, 20, 20};
    Ball pBall = {&ball, 1, 1, 3, 0};

    SDL_Rect paddleLeft = {20, 315, 20, 100};
    Paddle pPaddleLeft = {&paddleLeft, 0, 20};

    SDL_Rect paddleRight = {(SCREEN_WIDTH - paddleLeft.w - 20), 315, 20, 100};
    Paddle pPaddleRight = {&paddleRight, 0, 20};

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
        SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer->renderer);

        // Game logic and render updates go here
        // For example, drawing a white rectangle (like a pong paddleLeft)
        SDL_SetRenderDrawColor(renderer->renderer, 255, 255, 255, 255); // Set draw color to white

        Ball_handleCollision(&pBall, &pPaddleLeft, &pPaddleRight);
        Ball_setDirections(&pBall);

        Paddle_handlePaddlePosition(&pPaddleLeft, state);
        Paddle_setDirections(&pPaddleLeft);

        Paddle_handlePaddlePositionRight(&pPaddleRight, state);
        Paddle_setDirections(&pPaddleRight);

        SDL_RenderFillRect(renderer->renderer, &ball);
        SDL_RenderFillRect(renderer->renderer, &paddleLeft);
        SDL_RenderFillRect(renderer->renderer, &paddleRight);

        int drawLine = 1;
        while (drawLine)
        {
            SDL_RenderFillRect(renderer->renderer, &middleLine);
            middleLine.y += 10;

            if (middleLine.y > SCREEN_HEIGHT - middleLine.h)
            {
                drawLine = 0;
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer->renderer);

        // Delay to control frame rate
        middleLine.y = 0;
        SDL_Delay(16); // Approximately 60 frames per second (1000ms/60 ≈ 16ms per frame)
    }

    // Clean up before exiting
    SDL_Quit();
    return 0;
}
