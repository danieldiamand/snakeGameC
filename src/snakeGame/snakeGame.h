#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "./square.h"
#include "../input.h"

typedef struct
{
    Snake *snake;
    SquareType **board;
    Square *firstFood;
    int maxRow;
    int maxCol;
    bool gameover;
} SnakeGame;

SnakeGame *SnakeGame_new(int width, int height);
UpdatedSquares *SnakeGame_progress(SnakeGame *game, Input inputDirection);
void SnakeGame_free(SnakeGame *game);

#endif