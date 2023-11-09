#include "Ball.h"

void setMovingUp(Ball *ball, int value)
{
    ball->movingUp = value;
}

void setMovingLeft(Ball *ball, int value)
{
    ball->movingLeft = value;
}

void setVelocity(Ball *ball, int value)
{
    ball->velocity = value;
}

int getMovingUp(Ball *ball)
{
    return ball->movingUp;
}

int getMovingLeft(Ball *ball)
{
    return ball->movingLeft;
}

int getVelocity(Ball *ball)
{
    return ball->velocity;
}

// TODO: Make this 740 into a understandable code. Image width is supposed to be dynamic
int checkCollision(const Ball *ball, const Paddle *paddle)
{
    struct *rectBall = ball->ball;
    struct *rectPaddle = paddle->paddle;

    if (rectBall.y < 0)
    {
        setMovingUp(ball, 0);
    }
    else if (rectBall.y > 740)
    {
        setMovingUp(ball, 1);
    }
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
