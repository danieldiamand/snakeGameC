#ifndef SNAKE_H
#define SNAKE_H

#include "./square.h"
#include "../input.h"

typedef struct Node {
    Square *square;
    struct Node *next;
} Node;

Node *Node_new(Square *square, Node *next);

void Node_free(Node *node);

typedef struct Snake
{
    Node *head;
    Node *tail;
    Input direction;
} Snake;

Snake *Snake_new(Square *startPos);

void Snake_free(Snake *snake);

//updates the snakes direction
void Snake_updateDirection(Snake *snake, Input input);

//calculates the next square the snake will move into
Square *Snake_nextSquare(Snake *snake);

//moves snake into new square, doesn't shrink tail so snake grows
void Snake_moveGrow(Snake *snake, Square *square);

//moves snake into new square, shrinks tail and returns square it's left
Square *Snake_move(Snake *snake, Square *square);


#endif