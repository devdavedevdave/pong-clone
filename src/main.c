#include <SDL.h>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Player.h"

int main(int argc, char *argv[])
{
    Game *game = initGame();

    runGame(game);

    // Clean up before exiting
    SDL_Quit();
    return 0;
}
