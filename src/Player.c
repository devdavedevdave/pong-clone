#include "Player.h"
#include <stdlib.h>

// GETTERS
int Player_getPoints(Player *player) { return player->points; }

// LOGIC
void Player_incrementPoints(Player *player) { player->points++; }

void Player_renderPoints(Player *player, Renderer *renderer, int position) {
  int current = Player_getPoints(player);
  char current_str[12];
  sprintf(current_str, "%d", current);

  SDL_Color textColor = {255, 255, 255, 255}; // white color
  SDL_Surface *textSurface =
      TTF_RenderText_Blended(renderer->font, current_str, textColor);
  if (textSurface == NULL) {
    printf("TTF_RenderText: %s\n", TTF_GetError());
    return; // Exit the function if the surface wasn't created
  }

  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer->renderer, textSurface);
  if (textTexture == NULL) {
    printf("CreateTexture: %s\n", SDL_GetError());
    SDL_FreeSurface(textSurface); // Free the surface before returning
    return; // Exit the function if the texture wasn't created
  }

  // You must get the width and height before freeing the surface
  SDL_Rect textRect = {position, 24, textSurface->w, textSurface->h};
  SDL_FreeSurface(textSurface); // Surface can be freed after texture creation

  // Render the text texture
  SDL_RenderCopy(renderer->renderer, textTexture, NULL, &textRect);

  SDL_DestroyTexture(textTexture); // Destroy the texture after rendering
}

// MEMORY
void *Player_init() {
  Player *player = malloc(sizeof(Player));
  if (!player) {
    return NULL;
  }
  player->points = 0;

  return player;
}

void Player_destroy(Player *player) {
  if (player) {
    free(player);
  }
}
