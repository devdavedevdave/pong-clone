#include <SDL.h>

int main(int argc, char *argv[])
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;

    // Create a window with the specified position, dimensions, and flags
    window = SDL_CreateWindow(
        "SDL Pong",             // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        760,                    // width, in pixels
        760,                    // height, in pixels
        SDL_WINDOW_SHOWN        // flags - see below
    );

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = NULL;

    // Create a renderer for our window, using hardware acceleration and vsync
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;

    SDL_Rect paddleLeft = {25, 330, 20, 100};
    SDL_Rect paddleRight = {735, 330, 20, 100};
    SDL_Rect middleLine = {365, 0, 10, 5};
    int paddle_speed = 10;

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            // Additional event handling
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Move the paddleLeft up or down based on key presses
        if (state[SDL_SCANCODE_UP])
        {
            paddleLeft.y -= paddle_speed;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            paddleLeft.y += paddle_speed;
        }

        // Make sure the paddleLeft doesn't move out of the window
        if (paddleLeft.y < 0)
        {
            paddleLeft.y = 0;
        }
        else if (paddleLeft.y > (760 - paddleLeft.h))
        {
            paddleLeft.y = 760 - paddleLeft.h;
        }

        // Game logic and render updates go here
        // For example, drawing a white rectangle (like a pong paddleLeft)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white
        SDL_RenderFillRect(renderer, &paddleLeft);            // Draw the rectangle

        int drawLine = 1;

        while (drawLine)
        {
            SDL_RenderFillRect(renderer, &middleLine);
            middleLine.y += 10;

            if (middleLine.y > 760 - middleLine.h)
            {
                drawLine = 0;
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(16); // Approximately 60 frames per second (1000ms/60 ≈ 16ms per frame)
    }

    // Clean up before exiting
    SDL_Quit();
    return 0;
}
