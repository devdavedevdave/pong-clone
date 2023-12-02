#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    int points;
} Player;

void incrementPoints(Player *player);

int getPoints(Player *player);

#endif // PLAYER_H
