#include <SDL.h>
#include <stdio.h>
#include "Game.h"

Game *initGame()
{
    Game *game = malloc(sizeof(Game));
    if (game == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for game structure.\n");
        return NULL;
    }

    game->renderer = initRenderer();
    if (game->renderer == NULL)
    {
        fprintf(stderr, "Failed to initialize memory for renderer.\n");
        free(game);
        return NULL;
    }

    game->player1 = malloc(sizeof(Player));
    if (game->player1 == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for player1.\n");
        free(game->renderer);
        free(game);
        return NULL;
    }
    *(game->player1) = (Player){0};

    game->player2 = malloc(sizeof(Player));
    if (game->player2 == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for player1.\n");
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }
    *(game->player2) = (Player){0};

    game->ball = malloc(sizeof(Ball));
    if (game->ball == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Ball.\n");
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    game->ball->ball = malloc(sizeof(SDL_Rect));
    if (game->ball->ball == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for SDL_Rect.\n");
        free(game->ball);
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    *(game->ball->ball) = (SDL_Rect){370, 370, 20, 20};
    game->ball->movingUp = 1;
    game->ball->movingLeft = 1;
    game->ball->velocity = 3;
    game->ball->isInCollision = 0;

    game->paddleLeft = malloc(sizeof(Paddle));
    if (game->paddleLeft == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for SDL_Rect.\n");
        free(game->ball->ball);
        free(game->ball);
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    game->paddleLeft->paddle = malloc(sizeof(Paddle));
    if (game->paddleLeft->paddle == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for SDL_Rect.\n");
        free(game->paddleLeft);
        free(game->ball->ball);
        free(game->ball);
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    *(game->paddleLeft->paddle) = (SDL_Rect){20, 315, 20, 100};
    game->paddleLeft->movingUp = 0;
    game->paddleLeft->velocity = 20;

    game->paddleRight = malloc(sizeof(Paddle));
    if (game->paddleRight == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for SDL_Rect.\n");
        free(game->paddleLeft->paddle);
        free(game->paddleLeft);
        free(game->ball->ball);
        free(game->ball);
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    game->paddleRight->paddle = malloc(sizeof(SDL_Rect));
    if (game->paddleRight->paddle == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for SDL_Rect.\n");
        free(game->paddleRight);
        free(game->paddleLeft->paddle);
        free(game->paddleLeft);
        free(game->ball->ball);
        free(game->ball);
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    *(game->paddleRight->paddle) = (SDL_Rect){(SCREEN_WIDTH - game->paddleLeft->paddle->w - 20), 315, 20, 100};
    game->paddleRight->movingUp = 0;
    game->paddleRight->velocity = 20;

    game->middleLine = malloc(sizeof(SDL_Rect));
    if (game->middleLine == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for SDL_Rect.\n");
        free(game->paddleRight->paddle);
        free(game->paddleRight);
        free(game->paddleLeft->paddle);
        free(game->paddleLeft);
        free(game->ball->ball);
        free(game->ball);
        free(game->player2);
        free(game->player1);
        free(game->renderer);
        free(game);
        return NULL;
    }

    *(game->middleLine) = (SDL_Rect){365, 0, 10, 5};

    return game;
}

void runGame(Game *game)
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

void drawMiddleLine(SDL_Rect *middleLine, SDL_Renderer *renderer)
{
    int drawLine = 1;
    while (drawLine)
    {
        SDL_RenderFillRect(renderer, middleLine);
        middleLine->y += 10;

        if (middleLine->y > SCREEN_HEIGHT - middleLine->h)
        {
            drawLine = 0;
        }
    }
}