#include "./square.h"
#include <stdlib.h>
#include <stdbool.h>

Square Square_new(int row, int col, bool value){
    Square square;
    square.row = row;
    square.col = col;
    square.value = value;
    return square;
}

bool Square_samePos(Square square1, Square square2){
    return (square1.row == square2.row && square1.col == square2.col);
}