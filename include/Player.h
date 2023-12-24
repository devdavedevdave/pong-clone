#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    int points;
} Player;

// GETTERS
int getPoints(Player *player);

// LOGIC
void incrementPoints(Player *player);

// MEMORY
void *Player_init();

void Player_destroy(Player *player);

#endif // PLAYER_H
