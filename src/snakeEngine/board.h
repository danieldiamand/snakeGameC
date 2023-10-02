#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>


typedef union NodeData{
    Node* children[2];
    Square sqr;
} NodeData;


typedef struct Node{
    Node *parent;
    int trueSubtree;
    int totalSubtree;
    bool isBranch;
    NodeData data;
} Node;

typedef struct Board
{
    int rows;
    int cols;
    Node ***array;
} Board;


Board *Board_new(int rows, int cols);

void Board_free(Board *board);

void Board_putSquare(Board *board, Square square);

bool Board_isSquareSnakeOrWall(Board *board, Square square);

#endif