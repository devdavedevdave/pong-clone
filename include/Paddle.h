#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

struct Paddle
{
    SDL_Rect paddle;
    int velocity;
};

#endif // PADDLE_H