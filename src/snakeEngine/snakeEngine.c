#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../utils/square.h"
#include "./snake.h"
#include "./board.h"
#include "./snakeEngine.h"


Square _SnakeEngine_generateFood(SnakeEngine *game){
    Square food = Square_random(
        game->board->rows,
        game->board->cols,
        FOOD
    );

    while(_isSquareOnSnakeOrWall(game, food)){
        food = Square_random(game->board->rows, game->board->cols, FOOD);
    }

    return food;
}

SnakeEngine *SnakeEngine_new(int width, int height, int snakeRow, int snakeCol){
    SnakeEngine *game = malloc(sizeof(SnakeEngine));
    game->score = 1;
    game->board = Board_new(width, height);

    Square snakeHead = Square_random(
        snakeRow,
        snakeCol,
        SNAKE
    );
    _drawSquareOnBoard(game, snakeHead);
    game -> snake = Snake_new(snakeHead);

    Square *food = _generateFood(game);
    game->firstFood = food;
    _drawSquareOnBoard(game, food);

    return game;
}

void SnakeEngine_free(SnakeEngine *game){
    Snake_free(game -> snake);

    for (int x = 0; x <= game->maxRow; x++){
        free(game->board[x]);
    }
    free(game->firstFood);
    free(game->board); //NOT GOING TO WORK!!
    free(game);
}

UpdatedSquares *SnakeEngine_progress(SnakeEngine *game, Input inputDirection){
    UpdatedSquares *updatedSquares = malloc(sizeof(updatedSquares));
    Snake_updateDirection(game->snake, inputDirection);
    updatedSquares->snakesMovedInto = Snake_nextSquare(game->snake);
    if (_isSquareOnSnakeOrWall(game, updatedSquares->snakesMovedInto)){
        game ->gameover = true;
        return updatedSquares;
    }

    //if snake has eaten food
    if (game->board[updatedSquares->snakesMovedInto->row][updatedSquares->snakesMovedInto->col] == FOOD){
        game -> score ++;
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