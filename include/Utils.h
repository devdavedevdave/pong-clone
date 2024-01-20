#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include "Renderer.h"
#include "Game.h"

typedef enum {
   COLLIDE_LEFT,
   COLLIDE_RIGHT
} CollisionType;

Borders evaluateRectBorder(SDL_Rect *rect);

int isColliding(Borders *a, Borders *b, CollisionType type);

int clamp(const int value, const int min, const int max);

void drawMiddleLine(SDL_Rect *middleLine, SDL_Renderer *renderer);

// MEMORY
void *MiddleLine_init();

void MiddleLine_destroy(SDL_Rect *middleLine);

#endif // UTILS_H
