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
void handleWallCollision(const Ball *ball, const Paddle *paddle)
{
    SDL_Rect *rectBall = &(ball->ball);
    SDL_Rect *rectPaddle = &(paddle->paddle);

    if (rectBall->x <= 0 || rectBall->x >= 740)
    {
        goal(ball);
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

    int paddleYUpperLimit = rectPaddle->y;
    int paddleYLowerLimit = rectPaddle->y + rectPaddle->h;
    int paddleXLimit = rectPaddle->x >= 370 ? rectPaddle->x + 20 : rectPaddle->x;
    int ballYUpperLimit = rectBall->x;
    int ballYLowerLimit = rectBall->x + rectBall->h;
    int ballXLimit = rectBall->x >= 370 ? rectBall->x + 20 : rectBall->x;
}

// // Ball physics
// if (ball.y < 0)
// {
//     movingUp = 0;
// }
// else if (ball.y > 740)
// {
//     movingUp = 1;
// }
// else if (ball.y >= paddleLeft.y && (ball.y) <= (paddleLeft.y + paddleLeft.h) && ball.x <= (paddleLeft.x + paddleLeft.w))
// {
//     movingLeft = 0;
// }
// else if (ball.y >= paddleRight.y && (ball.y) <= (paddleRight.y + paddleRight.h) && (ball.x + ball.w) >= (paddleRight.x))
// {
//     movingLeft = 1;
// }

// // Changes the moving direction of the ball
// if (movingUp && movingLeft)
// {
//     ball.y -= velocity;
//     ball.x -= velocity;
// }
// else if (movingUp && !movingLeft)
// {
//     ball.y -= velocity;
//     ball.x += velocity;
// }
// else if (!movingUp && !movingLeft)
// {
//     ball.y += velocity;
//     ball.x += velocity;
// }
// else if (!movingUp && movingLeft)
// {
//     ball.y += velocity;
//     ball.x -= velocity;
// }