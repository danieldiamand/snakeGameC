#include "board.h"
#include "../utils/square.h"
#include <stdbool.h>
#include <stdlib.h>

Node *_Node_newSqr(int row, int col, bool val){
    Node *node = malloc(sizeof(Node));
    node -> isBranch = false;
    node -> data = (NodeData){.sqr = Square_new(row, col, val)};
    node -> trueSubtree = 0;
    node -> totalSubtree = 1;
    return node;
}

Node *_Node_newChildren(bool isBranch, Node *child1, Node *child2){
    Node *node = malloc(sizeof(Node));
    node -> isBranch = isBranch;
    node -> data = (NodeData){.children[0] = child1, .children[1] = child2};
    node -> trueSubtree = 0;
    node -> totalSubtree = node->data.children[0]->totalSubtree + node->data.children[1]->totalSubtree;

    return node;
}

Board *Board_new(int rows, int cols){
    Board *board = malloc(sizeof(board));
    board -> rows = rows;
    board -> cols = cols; 
    board ->array = malloc(rows * sizeof(Node*));
    for (int row = 0; row < rows; row++){
        board->array[row] = malloc(cols * sizeof(Node));
        for (int col = 0; col < cols; col++){
            board->array[row][col] = _Node_newSqr(row, col);
        }
    }

    return board;
}

void Board_free(Board *board){
        for (int row = 0; row < board->rows; row++){
            free(board->array[row]);
        }
        free(board);
}

void Board_putSquare(Board *board, Square square){
    board->array[square.row][square.col] = square.type;
}


bool Board_isSquareSnakeOrWall(Board *board, Square square){
    if (square.row < 0 
    || square.row >= board->rows
    || square.col < 0
    || square.col >= board->cols) return true;
    return board->array[square.row][square.col] == SNAKE;
}