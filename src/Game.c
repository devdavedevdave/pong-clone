#include <SDL.h>
#include <stdio.h>
#include "Game.h"
#include "Utils.h"

int initComponent(void **component, void *(*initFunc)())
{
    *component = initFunc();
    return *component != NULL;
}

Game *Game_init()
{
    Game *game = malloc(sizeof(Game));
    if (!game)
    {
        return NULL;
    }

    if (!initComponent((void **)&game->renderer, Renderer_init) ||
        !initComponent((void **)&game->player1, Player_init) ||
        !initComponent((void **)&game->player2, Player_init) ||
        !initComponent((void **)&game->ball, Ball_init) ||
        !initComponent((void **)&game->paddleLeft, PaddleLeft_init) ||
        !initComponent((void **)&game->paddleRight, PaddleRight_init) ||
        !initComponent((void **)&game->middleLine, MiddleLine_init))
    {
        Game_destroy(game);
        return NULL;
    }

    return game;
}

void Game_run(Game *game)
{
    SDL_Renderer *renderer = game->renderer->renderer;
    Player *player1 = game->player1;
    Player *player2 = game->player2;
    Ball *pBall = game->ball;
    SDL_Rect *ball = game->ball->ball;
    Paddle *pPaddleLeft = game->paddleLeft;
    SDL_Rect *paddleLeft = game->paddleLeft->paddle;
    Paddle *pPaddleRight = game->paddleRight;
    SDL_Rect *paddleRight = game->paddleRight->paddle;
    SDL_Rect *middleLine = game->middleLine;

    int running = 1;
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

        Ball_handleCollision(pBall, pPaddleLeft, pPaddleRight, player1, player2);
        Ball_setDirections(pBall);

        Paddle_handlePaddlePosition(pPaddleLeft, state);
        Paddle_setDirections(pPaddleLeft);

        Paddle_handlePaddlePositionRight(pPaddleRight, state);
        Paddle_setDirections(pPaddleRight);

        SDL_RenderFillRect(renderer, ball);
        SDL_RenderFillRect(renderer, paddleLeft);
        SDL_RenderFillRect(renderer, paddleRight);

        drawMiddleLine(middleLine, renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);

        middleLine->y = 0;
        // Delay to control frame rate
        SDL_Delay(16); // Approximately 60 frames per second (1000ms/60 ≈ 16ms per frame)
    }
}

void Game_destroy(Game *game)
{
    Player_destroy(game->player1);
    Player_destroy(game->player2);
    Ball_destroy(game->ball);
    Paddle_destroy(game->paddleLeft);
    Paddle_destroy(game->paddleRight);
    Renderer_destroy(game->renderer);
    MiddleLine_destroy(game->middleLine);
    free(game);
}