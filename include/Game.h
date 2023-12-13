#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Paddle.h"

#define SCREEN_WIDTH 760
#define SCREEN_HEIGHT 760
#define SCREEN_TOP 0
#define SCREEN_BOTTOM SCREEN_HEIGHT
#define BALL_SPAWN_X SCREEN_WIDTH / 2 - 10
#define BALL_SPAWN_Y SCREEN_HEIGHT / 2 - 10

typedef struct
{
    Renderer *renderer;
    Player *player1;
    Player *player2;
    Ball *ball;
    Paddle *paddleLeft;
    Paddle *paddleRight;
    SDL_Rect *middleLine;
} Game;

Game *Game_init();

void Game_run(Game *game);

void Game_destroy(Game *game);

#endif // GAME_H