#include <SDL.h>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Utils.h"

// GETTERS
int Ball_getMovingUp(const Ball *ball) { return ball->movingUp; }

int Ball_getMovingLeft(const Ball *ball) { return ball->movingLeft; }

int Ball_getVelocity(const Ball *ball) { return ball->velocity; }

// SETTERS
void Ball_setVelocity(Ball *ball, int value) { ball->velocity = value; }

void Ball_setDirections(Ball *ball)
{
    SDL_Rect *rectBall = ball->ball;
    int velocity = Ball_getVelocity(ball);

    rectBall->y += Ball_getMovingUp(ball) ? -velocity : velocity;
    rectBall->x += Ball_getMovingLeft(ball) ? -velocity : velocity;
}

// TOGGLERS
void Ball_toggleMovingUp(Ball *ball) { ball->movingUp = !ball->movingUp; }

void Ball_toggleMovingLeft(Ball *ball) { ball->movingLeft = !ball->movingLeft; }

// LOGIC
void handleWallCollision(Ball *ball)
{
    SDL_Rect *rectBall = ball->ball;

    if (rectBall->x <= 0 || rectBall->x >= SCREEN_WIDTH - rectBall->w)
    {
        // goal(ball);
        Ball_toggleMovingLeft(ball);

        rectBall->x = clamp(rectBall->x, 0, SCREEN_WIDTH - rectBall->w);
    }
    else if (rectBall->y <= 0 || rectBall->y >= SCREEN_BOTTOM - rectBall->h)
    {
        Ball_toggleMovingUp(ball);

        rectBall->y = clamp(rectBall->y, 0, SCREEN_HEIGHT - rectBall->y);
    }
}

void handlePaddleCollision(Ball *ball, Paddle *paddle)
{
    SDL_Rect *rectBall = ball->ball;
    const SDL_Rect *rectPaddle = paddle->paddle;

    // TODO: Try to do it with pointer, since it's repeting itself
    int paddleYUpperLimit = rectPaddle->y;
    int paddleYLowerLimit = rectPaddle->y + rectPaddle->h;
    int paddleXLimit = rectPaddle->x >= 370 ? rectPaddle->x + 20 : rectPaddle->x;
    int ballYUpperLimit = rectBall->y;
    // int ballYLowerLimit = rectBall->y + rectBall->h; // CHECK: Is this needed?
    int ballXLimit = rectBall->x >= 370 ? rectBall->x + 20 : rectBall->x;

    if (ballYUpperLimit >= paddleYUpperLimit && ballYUpperLimit <= paddleYLowerLimit && ballXLimit <= paddleXLimit)
    {
        Ball_toggleMovingLeft(ball);
    }
}

void handleCollision(Ball *ball, Paddle *paddle)
{
    handleWallCollision(ball);
    // handlePaddleCollision(ball, paddle);
}