#include "square.h"
#include "snake.h"
#include "../input.h"

#include <stdio.h>
#include <stdlib.h>

Node *Node_new(Square *square, Node *next){
    Node *node = malloc(sizeof(Node));
    *node = (Node){.square = square, .next = next};
    return node;
}

void Node_free(Node *node){
    free(node->square);
    free(node);
}


Snake *Snake_new(Square *startPos){
    Snake *snake = malloc(sizeof(snake));
    snake -> head = snake -> tail = Node_new(startPos, NULL);
    snake -> direction = RIGHT;
    return snake;
}

void Snake_free(Snake *snake){
    Node *current = snake -> tail;
    while (current != NULL){
        Node *next = current -> next;
        free(current);
        current = next;
    }
    free(snake);
}

void Snake_updateDirection(Snake *snake, Input input){
    // if (!((snake->direction == UP && input == DOWN)
    // || (snake->direction == DOWN && input == UP)
    // || (snake->direction == RIGHT && input == LEFT)
    // || (snake -> direction == LEFT && input == RIGHT)
    // || (input == NONE)
    // )) {
    //     snake -> direction = input; 
    // }
    if (input == NONE){
        return;
    }
    snake -> direction = input;
}

Square *Snake_nextSquare(Snake *snake){
    Square *old = snake -> head -> square;
    Input direction = snake -> direction;
    if (direction == UP) return Square_new(old->row, old ->col -1, SNAKE);
    if (direction == DOWN) return Square_new(old->row, old ->col +1, SNAKE);
    if (direction == RIGHT)return Square_new(old->row+1, old ->col, SNAKE);
    if (direction == LEFT)return Square_new(old->row-1, old ->col, SNAKE);
    return NULL;
}

void Snake_moveGrow(Snake *snake, Square *square){
    Node *node = Node_new(square, NULL);
    snake -> head -> next = node;
    snake -> head = node;
}

Square *Snake_move(Snake *snake, Square *square){
    Snake_moveGrow(snake, square);
    
    //shrink tail
    Node *oldTail = snake -> tail;
    snake -> tail = snake -> tail -> next;
    Square *oldSquare = oldTail -> square;
    free(oldTail);
    oldSquare -> type = EMPTY;
    return oldSquare;
}

