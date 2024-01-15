
#include "Game.h"
#include "Utils.h"

// LOGIC
void Game_clear(Game *game)
{
    SDL_Renderer *renderer = game->renderer->renderer;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Game_updateState(Game *game)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    Ball_handleCollision(game->ball, game->paddleLeft, game->paddleRight, game->player1, game->player2);
    Ball_setDirections(game->ball);

    Paddle_handlePaddlePosition(game->paddleLeft, state);
    Paddle_setDirections(game->paddleLeft);

    Paddle_handlePaddlePositionRight(game->paddleRight, state);
    Paddle_setDirections(game->paddleRight);
}

void Game_renderElements(Game *game)
{
    SDL_Renderer *renderer = game->renderer->renderer;
    SDL_Rect *ball = game->ball->ball;
    SDL_Rect *paddleLeft = game->paddleLeft->paddle;
    SDL_Rect *paddleRight = game->paddleRight->paddle;
    SDL_Rect *middleLine = game->middleLine;

    SDL_RenderFillRect(renderer, ball);
    SDL_RenderFillRect(renderer, paddleLeft);
    SDL_RenderFillRect(renderer, paddleRight);
    drawMiddleLine(middleLine, renderer);

    SDL_RenderPresent(game->renderer->renderer);

    middleLine->y = 0;
}

// MEMORY
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

        Game_clear(game);

        Game_updateState(game);

        Game_renderElements(game);

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
