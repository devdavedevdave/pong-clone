#include <stdlib.h>
#include "Player.h"

// GETTERS
int getPoints(Player *player) { return player->points; }

// LOGIC
void incrementPoints(Player *player) { player->points++; }

// MEMORY
Player *Player_init()
{
    Player *player = malloc(sizeof(Player));
    if (!player)
    {
        return NULL;
    }
    player->points = 0;

    return player;
}

void Player_destroy(Player *player)
{
    if (player)
    {
        free(player);
    }
}