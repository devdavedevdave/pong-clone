#include "Paddle.h"

void Paddle_setMovingUp(Paddle *paddle, int value)
{
    paddle->movingUp = value;
}

int Paddle_getMovingUp(Paddle *paddle)
{
    return paddle->movingUp;
}

int Paddle_getVelocity(Paddle *paddle)
{
    return paddle->velocity;
}

void Paddle_setPaddleMovement(Paddle *paddle)
{
    SDL_Rect *rectPaddle = paddle->paddle;

    rectPaddle->y += Paddle_getMovingUp(paddle) ? -Paddle_getVelocity(paddle) : Paddle_getVelocity(paddle);
}

void Paddle_handlePaddlePosition(Paddle *paddle, const Uint8 *state)
{
    if (state[SDL_SCANCODE_UP])
    {
        Paddle_setMovingUp(paddle, 1);
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
        Paddle_setMovingUp(paddle, 0);
    }
}

// // Make sure the paddleLeft doesn't move out of the window
// if (paddleLeft.y < 0)
// {
//     paddleLeft.y = 0;
// }
// else if (paddleLeft.y > (760 - paddleLeft.h))
// {
//     paddleLeft.y = 760 - paddleLeft.h;
// }