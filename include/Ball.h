#ifndef BALL_H
#define BALL_H

#include <SDL.h>

typedef struct
{
    SDL_Rect ball;
    int movingUp;
    int movingLeft;
    int velocity;
} Ball;

void setMovingUp(Ball *ball, int value);

void setMovingLeft(Ball *ball, int value);

void setVelocity(Ball *ball, int value);

int getMovingUp(const Ball *ball);

int getMovingLeft(const Ball *ball);

int getVelocity(const Ball *ball);

int checkCollision(const Ball *ball);

#endif // BALL_H