#include "./square.h"
#include <stdlib.h>
#include <stdbool.h>

Square *Square_new(int row, int col, SquareType type){
    Square *square = malloc(sizeof(Square));
    square -> row = row;
    square -> col = col;
    square -> type = type;
    return square;
}

Square *Square_random(int maxRow, int maxCol, SquareType type){
    return Square_new(
        rand() % (maxRow + 1),
        rand() % (maxCol + 1),
        type);
}

bool Square_samePos(Square *square1, Square * square2){
    return (square1->row == square2 ->row && square1->col == square2 -> col);
}