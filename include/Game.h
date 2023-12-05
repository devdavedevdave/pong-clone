#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Renderer.h"

#define SCREEN_WIDTH 760
#define SCREEN_HEIGHT 760
#define SCREEN_TOP 0
#define SCREEN_BOTTOM SCREEN_HEIGHT
#define BALL_SPAWN_X SCREEN_WIDTH / 2 - 10
#define BALL_SPAWN_Y SCREEN_HEIGHT / 2 - 10

void drawMiddleLine(SDL_Rect *middleLine, Renderer *renderer);

#endif // GAME_H