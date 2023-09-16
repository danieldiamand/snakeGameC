#ifndef SQUARE_H
#define SQUARE_H

#include <stdbool.h>

typedef enum {
    EMPTY,
    SNAKE,
    FOOD
} SquareType;

typedef struct
{
    int row;
    int col;
    SquareType type;
} Square;

typedef struct {
    Square *snakesMovedInto;
    Square *snakesLeft;
    Square *food;
} UpdatedSquares;

Square *Square_new(int row, int col, SquareType type);

Square *Square_random(int maxRow, int maxCol, SquareType type);

bool Square_samePos(Square *square1, Square * square2);

#endif