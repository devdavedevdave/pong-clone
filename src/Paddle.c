#include "Game.h"
#include "Utils.h"
#include "Paddle.h"

// GETTER
int Paddle_getMovingUp(const Paddle *paddle) { return paddle->movingUp; }

int Paddle_getVelocity(const Paddle *paddle) { return paddle->velocity; }

// SETTER
void Paddle_setMovingUp(Paddle *paddle, int value) { paddle->movingUp = value; }

void Paddle_setVelocity(Paddle *paddle, int value) { paddle->velocity = value; }

// LOGIC
void Paddle_setPaddleMovement(Paddle *paddle)
{
    const int SCREEN_TOP = 0;
    const int SCREEN_BOTTOM = SCREEN_HEIGHT;

    SDL_Rect *rectPaddle = paddle->paddle;
    int moveDirection = Paddle_getMovingUp(paddle);

    // Move paddle and ensure staying in screen with clamp
    if (moveDirection != 0)
        rectPaddle->y = clamp(rectPaddle->y + moveDirection * Paddle_getVelocity(paddle), SCREEN_TOP, SCREEN_BOTTOM - rectPaddle->h);
}

void Paddle_handlePaddlePosition(Paddle *paddle, const Uint8 *state)
{
    int moveDirection = (state[SDL_SCANCODE_UP] ? -1 : (state[SDL_SCANCODE_DOWN] ? 1 : 0));

    Paddle_setMovingUp(paddle, moveDirection);
}