#ifndef SNAKEENGINE_H
#define SNAKEENGINE_H
#include "snake.h"
#include "board.h"

typedef struct
{
    Snake *snake;
    Board *board;
    Square *firstFood;
    int score;
} SnakeEngine;

SnakeEngine *SnakeEngine_new(int width, int height, int snakeRow, int snakeCol);

UpdatedSquares *SnakeEngine_progress(SnakeEngine *game, Direction input);

void SnakeEngine_free(SnakeEngine *game);

#endif