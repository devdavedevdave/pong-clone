#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "Paddle.h"

typedef struct
{
    SDL_Rect *ball;
    int movingUp;
    int movingLeft;
    int velocity;
} Ball;

void Ball_toggleMovingUp(Ball *ball);

void Ball_toggleMovingLeft(Ball *ball);

void Ball_setVelocity(Ball *ball, int value);

int Ball_getMovingUp(const Ball *ball);

int Ball_getMovingLeft(const Ball *ball);

int Ball_getVelocity(const Ball *ball);

void Ball_setDirections(Ball *ball);

void handleWallCollision(Ball *ball);

void handlePaddleCollision(Ball *ball, Paddle *paddle);

void handleCollision(Ball *ball, Paddle *paddle);

#endif // BALL_H