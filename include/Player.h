#ifndef PLAYER_H
#define PLAYER_H

#include "Renderer.h"

typedef struct {
  int points;
} Player;

// GETTERS
int Player_getPoints(Player *player);

// LOGIC
void Player_incrementPoints(Player *player);

void Player_renderPoints(Player *player, Renderer *renderer, int position);

// MEMORY
void *Player_init();

void Player_destroy(Player *player);

#endif // PLAYER_H
