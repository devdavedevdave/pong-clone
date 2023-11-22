#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

typedef struct
{
    SDL_Rect *paddle;
    int movingUp;
    int velocity;
} Paddle;

void Paddle_setMovingUp(Paddle *paddle, int value);

int Paddle_getMovingUp(Paddle *paddle);

int Paddle_getVelocity(Paddle *paddle);

void Paddle_setPaddleMovement(Paddle *paddle);

void Paddle_handlePaddlePosition(Paddle *paddle, const Uint8 *state);

#endif // PADDLE_H