#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "Paddle.h"
#include "Player.h"

typedef struct
{
    SDL_Rect *ball;
    int movingUp;
    int movingLeft;
    int velocity;
    int isInCollision;
} Ball;

typedef struct
{
    int top;
    int bottom;
    int left;
    int right;
} Borders;

// GETTER
int Ball_getMovingUp(const Ball *ball);

int Ball_getMovingLeft(const Ball *ball);

int Ball_getVelocity(const Ball *ball);

// SETTERS
void Ball_setVelocity(Ball *ball, int value);

void Ball_setMovingUp(Ball *ball);

void Ball_setMovingDown(Ball *ball);

void Ball_setMovingNeutral(Ball *ball);

void Ball_setMovement(Ball *ball);

void Ball_setDirection(Ball *ball, Borders *ballBorder, Borders *paddleBorder);

// TOGGLERS
void Ball_toggleMovingLeft(Ball *ball);

void Ball_toggleMovingUp(Ball *ball);

// LOGIC
void Ball_handleWallCollision(Ball *ball, Player *player1, Player *player2);

void Ball_handlePaddleCollision(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle);

void Ball_handleCollision(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle, Player *player1, Player *player2);

// MEMORY
void *Ball_init();

void Ball_destroy(Ball *ball);

#endif // BALL_H
