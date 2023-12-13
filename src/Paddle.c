#include "Game.h"
#include "Utils.h"
#include "Paddle.h"

// GETTER
int Paddle_getMovingUp(const Paddle *paddle) { return paddle->movingUp; }

int Paddle_getVelocity(const Paddle *paddle) { return paddle->velocity; }

// SETTER
void Paddle_setMovingUp(Paddle *paddle, int value) { paddle->movingUp = value; }

void Paddle_setVelocity(Paddle *paddle, int value) { paddle->velocity = value; }

void Paddle_setDirections(Paddle *paddle)
{
    SDL_Rect *rectPaddle = paddle->paddle;
    int moveDirection = Paddle_getMovingUp(paddle);

    // Move paddle and ensure staying in screen with clamp
    if (moveDirection != 0)
        rectPaddle->y = clamp(rectPaddle->y + moveDirection * Paddle_getVelocity(paddle), SCREEN_TOP, SCREEN_BOTTOM - rectPaddle->h);
}

// LOGIC
void Paddle_handlePaddlePosition(Paddle *paddle, const Uint8 *state)
{
    int moveDirection = (state[SDL_SCANCODE_UP] ? -1 : (state[SDL_SCANCODE_DOWN] ? 1 : 0));

    Paddle_setMovingUp(paddle, moveDirection);
}

void Paddle_handlePaddlePositionRight(Paddle *paddle, const Uint8 *state)
{
    int moveDirection = (state[SDL_SCANCODE_W] ? -1 : (state[SDL_SCANCODE_S] ? 1 : 0));

    Paddle_setMovingUp(paddle, moveDirection);
}

// MEMORY
Paddle *Paddle_init(int posX, int posY, int width, int height)
{
    Paddle *paddle = malloc(sizeof(Paddle));
    if (!paddle)
    {
        return NULL;
    }

    paddle->paddle = malloc(sizeof(SDL_Rect));
    if (!paddle->paddle)
    {
        free(paddle);
        return NULL;
    }

    *(paddle->paddle) = (SDL_Rect){posX, posY, width, height};
    paddle->movingUp = 0;
    paddle->velocity = 20;

    return paddle;
}

void Paddle_destroy(Paddle *paddle)
{
    if (paddle)
    {
        free(paddle->paddle);
        free(paddle);
    }
}