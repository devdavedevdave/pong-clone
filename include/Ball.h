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

typedef enum
{
    COLLIDE_LEFT,
    COLLIDE_RIGHT
} CollisionType;

// GETTER
int Ball_getMovingUp(const Ball *ball);

int Ball_getMovingLeft(const Ball *ball);

int Ball_getVelocity(const Ball *ball);

// SETTER
void Ball_setDirections(Ball *ball);

void Ball_setVelocity(Ball *ball, int value);

// TOGGLERS
void Ball_toggleMovingUp(Ball *ball);

void Ball_toggleMovingLeft(Ball *ball);

// LOGIC
void Ball_handleWallCollision(Ball *ball, Player *player1, Player *player2);

void Ball_handlePaddleCollision(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle);

void Ball_handleCollision(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle, Player *player1, Player *player2);

#endif // BALL_H
