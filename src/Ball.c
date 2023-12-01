#include <SDL.h>
#include <stdio.h>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Utils.h"

// GETTERS
int Ball_getMovingUp(const Ball *ball) { return ball->movingUp; }

int Ball_getMovingLeft(const Ball *ball) { return ball->movingLeft; }

int Ball_getVelocity(const Ball *ball) { return ball->velocity; }

// SETTERS
void Ball_setVelocity(Ball *ball, int value) { ball->velocity = value; }

void Ball_setDirections(Ball *ball)
{
    SDL_Rect *rectBall = ball->ball;
    int velocity = Ball_getVelocity(ball);

    rectBall->y += Ball_getMovingUp(ball) ? -velocity : velocity;
    rectBall->x += Ball_getMovingLeft(ball) ? -velocity : velocity;
}

// TOGGLERS
void Ball_toggleMovingUp(Ball *ball) { ball->movingUp = !ball->movingUp; }

void Ball_toggleMovingLeft(Ball *ball) { ball->movingLeft = !ball->movingLeft; }

// LOGIC
void Ball_handleWallCollision(Ball *ball)
{
    SDL_Rect *rectBall = ball->ball;

    // Check for horizontal collision
    if (rectBall->x <= 0 || rectBall->x >= SCREEN_WIDTH - rectBall->w)
    {
        // goal(player);
        Ball_toggleMovingLeft(ball);
        rectBall->x = clamp(rectBall->x, 0, SCREEN_WIDTH - rectBall->w);
    }

    // Check for vertical collision
    if (rectBall->y <= 0 || rectBall->y >= SCREEN_BOTTOM - rectBall->h)
    {
        Ball_toggleMovingUp(ball);
        rectBall->y = clamp(rectBall->y, 0, SCREEN_HEIGHT - rectBall->h);
    }
}

void Ball_handlePaddleCollision(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle)
{
    Borders ballBorders = evaluateRectBorder(ball->ball);
    Borders leftPaddleBorders = evaluateRectBorder(leftPaddle->paddle);
    Borders rightPaddleBorders = evaluateRectBorder(rightPaddle->paddle);

    if (!ball->isInCollision)
    {
        // Check collision with left paddle
        if (isColliding(&ballBorders, &leftPaddleBorders, COLLIDE_LEFT))
        {
            printf("left\n");
            Ball_toggleMovingLeft(ball);
            ball->isInCollision = 1;
        }
        // Check collision with right paddle
        else if (isColliding(&ballBorders, &rightPaddleBorders, COLLIDE_RIGHT))
        {
            printf("right\n");
            Ball_toggleMovingLeft(ball);
            ball->isInCollision = 1;
        }
    }
    else if (!isColliding(&ballBorders, &leftPaddleBorders, COLLIDE_LEFT) && !isColliding(&ballBorders, &rightPaddleBorders, COLLIDE_RIGHT))
    {
        printf("collision ended\n");
        ball->isInCollision = 0;
    }
}

void Ball_handleCollision(Ball *ball, Paddle *paddleLeft, Paddle *paddleRight)
{
    Ball_handleWallCollision(ball);
    Ball_handlePaddleCollision(ball, paddleLeft, paddleRight);
}