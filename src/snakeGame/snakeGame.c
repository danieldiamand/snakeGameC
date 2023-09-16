#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "./square.h"
#include "./Snake.h"
#include "./snakeGame.h"

void _drawSquareOnBoard(SnakeGame *game, Square *square){
    game->board[square->row][square->col] = square->type;
}

//returns true if square is in same pos as snake
bool _isSquareOnSnakeOrWall(SnakeGame *game, Square *square){
    if (square->row < 0 
    || square->row > game->maxRow
    || square->col < 0
    || square->col > game->maxCol) return true;
    return game->board[square->row][square->col] == SNAKE;
}

Square *_generateFood(SnakeGame *game){
    Square *food = Square_random(
        game->maxRow,
        game->maxCol,
        FOOD
    );

    while(_isSquareOnSnakeOrWall(game, food)){
        free(food);
        food = Square_random(game->maxRow, game->maxCol, FOOD);
    }

    return food;
}

SnakeGame *SnakeGame_new(int width, int height){

    
    SnakeGame *game = malloc(sizeof(SnakeGame));
    game -> gameover = false;
    game->maxRow = width - 1;
    game->maxCol = height - 1;

    game->board = malloc(width * sizeof(SquareType*));
    for (int x = 0; x < width; x++){
        game->board[x] = malloc(height * sizeof(SquareType));
        for (int y = 0; y < height; y++){
            game->board[x][y] = EMPTY;
        }
    }

    Square *snakeHead = Square_random(
        game->maxRow,
        game->maxCol,
        SNAKE
    );
    _drawSquareOnBoard(game, snakeHead);
    game -> snake = Snake_new(snakeHead);

    Square *food = _generateFood(game);
    game->firstFood = food;
    _drawSquareOnBoard(game, food);

    return game;
}

void SnakeGame_free(SnakeGame *game){
    Snake_free(game -> snake);

    for (int x = 0; x <= game->maxRow; x++){
        free(game->board[x]);
    }
    free(game->firstFood);
    free(game->board); //NOT GOING TO WORK!!
    free(game);
}

UpdatedSquares *SnakeGame_progress(SnakeGame *game, Input inputDirection){
    UpdatedSquares *updatedSquares = malloc(sizeof(updatedSquares));
    Snake_updateDirection(game->snake, inputDirection);
    updatedSquares->snakesMovedInto = Snake_nextSquare(game->snake);
    if (_isSquareOnSnakeOrWall(game, updatedSquares->snakesMovedInto)){
        game ->gameover = true;
        return updatedSquares;
    }

    //if snake has eaten food
    if (game->board[updatedSquares->snakesMovedInto->row][updatedSquares->snakesMovedInto->col] == FOOD){
        Snake_moveGrow(game->snake, updatedSquares->snakesMovedInto);
        _drawSquareOnBoard(game, updatedSquares->snakesMovedInto); //draw square snakes moved into
        updatedSquares->food = _generateFood(game);
        _drawSquareOnBoard(game, updatedSquares -> food); 
        updatedSquares->snakesLeft = NULL;
    }else{
        updatedSquares ->snakesLeft = Snake_move(game->snake, updatedSquares->snakesMovedInto);
        updatedSquares->food = NULL;
    }

    return updatedSquares;
};