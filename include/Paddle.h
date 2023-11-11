#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

typedef struct
{
    SDL_Rect paddle;
    int velocity;
} Paddle;

#endif // PADDLE_H