#ifndef SQUARE_H
#define SQUARE_H

#include <stdbool.h>


typedef struct Square
{
    int row;
    int col;
    bool value;
} Square;

typedef struct UpdatedSquares{
    bool gameOver;
    bool snakeGrown;
    Square snakesMovedInto;
    Square snakesMovedOut;
    Square food;
} UpdatedSquares;

Square Square_new(int row, int col, bool type);

bool Square_samePos(Square square1, Square square2);

#endif