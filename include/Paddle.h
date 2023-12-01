#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

typedef struct
{
    SDL_Rect *paddle;
    int movingUp;
    int velocity;
} Paddle;

// GETTER
int Paddle_getMovingUp(const Paddle *paddle);

int Paddle_getVelocity(const Paddle *paddle);

// SETTER
void Paddle_setMovingUp(Paddle *paddle, int value);

void Paddle_setVelocity(Paddle *paddle, int value);

void Paddle_setDirections(Paddle *paddle);

// LOGIC
void Paddle_handlePaddlePosition(Paddle *paddle, const Uint8 *state);

void Paddle_handlePaddlePositionRight(Paddle *paddle, const Uint8 *state);

#endif // PADDLE_H