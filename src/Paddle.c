// // Move the paddleLeft up or down based on key presses
// if (state[SDL_SCANCODE_UP])
// {
//     paddleLeft.y -= paddle_speed;
// }
// if (state[SDL_SCANCODE_DOWN])
// {
//     paddleLeft.y += paddle_speed;
// }

// // Make sure the paddleLeft doesn't move out of the window
// if (paddleLeft.y < 0)
// {
//     paddleLeft.y = 0;
// }
// else if (paddleLeft.y > (760 - paddleLeft.h))
// {
//     paddleLeft.y = 760 - paddleLeft.h;
// }