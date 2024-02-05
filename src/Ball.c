#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "Player.h"
#include "Utils.h"
#include <SDL.h>
#include <stdio.h>

// GETTERS
int Ball_getMovingUp(const Ball *ball) { return ball->movingUp; }

int Ball_getMovingLeft(const Ball *ball) { return ball->movingLeft; }

int Ball_getVelocity(const Ball *ball) { return ball->velocity; }

// SETTERS
void Ball_setVelocity(Ball *ball, int value) { ball->velocity = value; }

void Ball_setMovingUp(Ball *ball) { ball->movingUp = 1; }

void Ball_setMovingDown(Ball *ball) { ball->movingUp = -1; }

void Ball_setMovingNeutral(Ball *ball) { ball->movingUp = 0; }

void Ball_setMovement(Ball *ball) {
  SDL_Rect *rectBall = ball->ball;
  int velocity = Ball_getVelocity(ball);

  if (Ball_getMovingUp(ball) != 0) {
    rectBall->y += Ball_getMovingUp(ball) == 1 ? -velocity : velocity;
  }

  rectBall->x += Ball_getMovingLeft(ball) ? -velocity : velocity;
}

void Ball_setDirection(Ball *ball, Borders *ballBorder, Borders *paddleBorder) {
  const int paddle_segment = (paddleBorder->bottom - paddleBorder->top) / 3;
  for (int i = 1; i <= 3; i++) {
    if (ballBorder->top < paddleBorder->top + paddle_segment * i) {
      switch (i) {
      case 1:
        Ball_setMovingUp(ball);
        break;
      case 2:
        Ball_setMovingNeutral(ball);
        break;
      case 3:
        Ball_setMovingDown(ball);
        break;
      }
      break;
    }
  }

  Ball_setVelocity(ball, Ball_getVelocity(ball) + 1);
  Ball_toggleMovingLeft(ball);
}

// TOGGLERS
void Ball_toggleMovingLeft(Ball *ball) { ball->movingLeft = !ball->movingLeft; }

void Ball_toggleMovingUp(Ball *ball) {
  ball->movingUp == 1 ? Ball_setMovingDown(ball) : Ball_setMovingUp(ball);
}

// LOGIC
void Ball_handleWallCollision(Ball *ball, Player *player1, Player *player2) {
  SDL_Rect *rectBall = ball->ball;

  // Check for horizontal collision and score points
  if (rectBall->x <= 0) {
    Player_incrementPoints(player2);
  } else if (rectBall->x >= SCREEN_WIDTH - rectBall->w) {
    Player_incrementPoints(player1);
  }

  // Check for horizontal collision and perform respawn
  if (rectBall->x <= 0 || rectBall->x >= SCREEN_WIDTH - rectBall->w) {
    Ball_setVelocity(ball, 4);
    const int BALL_SPAWN_X = SCREEN_WIDTH / 2 - 10;
    const int BALL_SPAWN_Y = (int)((double)rand() / RAND_MAX * SCREEN_HEIGHT);

    if (rand() % 2) {
      Ball_toggleMovingLeft(ball);
    }

    rectBall->x = BALL_SPAWN_X;
    rectBall->y = BALL_SPAWN_Y;
  }

  // Check for vertical collision
  if (rectBall->y <= 0 || rectBall->y >= SCREEN_BOTTOM - rectBall->h) {
    Ball_toggleMovingUp(ball);
    rectBall->y = clamp(rectBall->y, 0, SCREEN_HEIGHT - rectBall->h);
  }
}

void Ball_handlePaddleCollision(Ball *ball, Paddle *leftPaddle,
                                Paddle *rightPaddle) {
  Borders ballBorders = evaluateRectBorder(ball->ball);
  Borders leftPaddleBorders = evaluateRectBorder(leftPaddle->paddle);
  Borders rightPaddleBorders = evaluateRectBorder(rightPaddle->paddle);

  if (!ball->isInCollision) {
    // Check collision with paddle
    if (isColliding(&ballBorders, &leftPaddleBorders, COLLIDE_LEFT)) {
      Ball_setDirection(ball, &ballBorders, &leftPaddleBorders);
      ball->isInCollision = 1;
    } else if (isColliding(&ballBorders, &rightPaddleBorders, COLLIDE_RIGHT)) {
      Ball_setDirection(ball, &ballBorders, &rightPaddleBorders);
      ball->isInCollision = 1;
    }
  } else if (!isColliding(&ballBorders, &leftPaddleBorders, COLLIDE_LEFT) &&
             !isColliding(&ballBorders, &rightPaddleBorders, COLLIDE_RIGHT)) {
    ball->isInCollision = 0;
  }
}

void Ball_handleCollision(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle,
                          Player *player1, Player *player2) {
  Ball_handleWallCollision(ball, player1, player2);
  Ball_handlePaddleCollision(ball, leftPaddle, rightPaddle);
}

// MEMORY
void *Ball_init() {
  Ball *ball = malloc(sizeof(Ball));
  if (!ball) {
    return NULL;
  }

  ball->ball = malloc(sizeof(SDL_Rect));
  if (!ball->ball) {
    free(ball);
    return NULL;
  }

  *(ball->ball) = (SDL_Rect){370, 370, 20, 20};
  ball->movingUp = 1;
  ball->movingLeft = 1;
  ball->velocity = 4;
  ball->isInCollision = 0;

  return ball;
}

void Ball_destroy(Ball *ball) {
  if (ball) {
    free(ball->ball);
    free(ball);
  }
}
