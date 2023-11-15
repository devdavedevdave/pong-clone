#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"

void toggleMovingUp(Ball *ball)
{
    ball->movingUp = !ball->movingUp;
}

void toggleMovingLeft(Ball *ball)
{
    ball->movingLeft = !ball->movingLeft;
}

void setVelocity(Ball *ball, int value)
{
    ball->velocity = value;
}

int getMovingUp(const Ball *ball)
{
    return ball->movingUp;
}

int getMovingLeft(const Ball *ball)
{
    return ball->movingLeft;
}

int getVelocity(const Ball *ball)
{
    return ball->velocity;
}

// TODO: Make this 740 into a understandable code. Image width is supposed to be dynamic
// Use macros for the conditions in the if and else

// TODO: Implement goal() function
void handleWallCollision(const Ball *ball)
{
    SDL_Rect *rectBall = &(ball->ball);

    if (rectBall->x <= 0 || rectBall->x >= 740)
    {
        // goal(ball);
        toggleMovingLeft(ball);
    }
    else if (rectBall->y <= 0 || rectBall->y >= 740)
    {
        toggleMovingUp(ball);
    }
}

void handlePaddleCollision(const Ball *ball, const Paddle *paddle)
{
    SDL_Rect *rectBall = &(ball->ball);
    SDL_Rect *rectPaddle = &(paddle->paddle);

    // TODO: Try to do it with pointer, since it's repeting itself
    int paddleYUpperLimit = rectPaddle->y;
    int paddleYLowerLimit = rectPaddle->y + rectPaddle->h;
    int paddleXLimit = rectPaddle->x >= 370 ? rectPaddle->x + 20 : rectPaddle->x;
    int ballYUpperLimit = rectBall->y;
    int ballYLowerLimit = rectBall->y + rectBall->h;
    int ballXLimit = rectBall->x >= 370 ? rectBall->x + 20 : rectBall->x;

    if (ballYUpperLimit >= paddleYUpperLimit && ballYUpperLimit <= paddleYLowerLimit && ballXLimit <= paddleXLimit)
    {
        toggleMovingLeft(ball);
    }
}

void handleCollision(const Ball *ball, const Paddle *paddle)
{
    handleWallCollision(ball);
    handlePaddleCollision(ball, paddle);
}

void setDirections(Ball *ball)
{
    SDL_Rect *rectBall = &(ball->ball);
    int velocity = ball->velocity;

    rectBall->y += getMovingUp(ball) ? -velocity : velocity;
    rectBall->x += getMovingLeft(ball) ? -velocity : velocity;
}