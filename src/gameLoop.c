#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "./input.h"
#include "./snakeEngine/square.h"
#include "./snakeEngine/snake.h"
#include "./snakeEngine/snakeGame.h"

typedef struct
{
    int sqr_size;
    int spacing;
} Data;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SnakeGame *snakeGame;
    Data *data;
} Game;

bool _initWindowRenderer(Game *game, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    game->window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN // not sure about which thing i should use here
    );
    if (!game->window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0); // gpt suggests sdl_render_accelrate
    if (!game->renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }

    return true;
}

void _freeWindowRenderer(Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

void _drawSquare(Game *game, int row, int col)
{
    const int sqr_size = game->data->sqr_size;
    const int spacing = game->data->spacing;
    SDL_Rect rect = {row * (sqr_size + spacing), col * (sqr_size + spacing), sqr_size, sqr_size};
    SDL_RenderFillRect(game->renderer, &rect);
}

void _drawGrid(Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, 150, 150, 150, 255);
    for (int row = 0; row <= game->snakeGame->maxRow; row++)
    {
        for (int col = 0; col <= game->snakeGame->maxCol; col++)
        {
            _drawSquare(game, row, col);
        }
    }
}

void _updateInput(Game *game, Input *input)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->snakeGame->gameover = true;
        return;
    }
    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            game->snakeGame->gameover = true;
            return;
        case SDLK_w:
            *input = UP;
            return;
        case SDLK_UP:
            *input = UP;
            return;
        case SDLK_s:
            *input = DOWN;
            return;
        case SDLK_DOWN:
            *input = DOWN;
            return;
        case SDLK_d:
            *input = RIGHT;
            return;
        case SDLK_RIGHT:
            *input = RIGHT;
            return;
        case SDLK_a:
            *input = LEFT;
            return;
        case SDLK_LEFT:
            *input = LEFT;
            return;
        }
    }
    return;
}


#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

void _pauseToFrame(int *lastFrameTime){
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - *lastFrameTime);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    //float delta_time = (SDL_GetTicks() - *lastFrameTime) / 1000.0;

    *lastFrameTime = SDL_GetTicks();
}

UpdatedSquares *_update(Game *game, Input input, int *lastFrameTime){
    //put code here maybe?
    UpdatedSquares *updatedSquares = SnakeGame_progress(game->snakeGame, input);
    //ensuring constant framerate
    _pauseToFrame(lastFrameTime);

    return updatedSquares;
}

void _render(Game *game, Square *snakesMovedInto, Square *snakesLeft, Square *food){
    
    if (game->snakeGame->gameover){
        SDL_SetRenderDrawColor(game->renderer, 150, 150, 150, 255);
        Node *current = game->snakeGame->snake-> tail;
        while (current != NULL){
            _drawSquare(game, current->square->row, current->square->col);
            current = current -> next;
        SDL_RenderPresent(game->renderer);
        SDL_Delay(500);
        return;
        }
    }
    if (snakesMovedInto != NULL){
        SDL_SetRenderDrawColor(game->renderer, 14, 138, 51, 255);
        _drawSquare(game, snakesMovedInto->row, snakesMovedInto->col);
    }
    if (snakesLeft != NULL){
        SDL_SetRenderDrawColor(game->renderer, 150, 150, 150, 255);
        _drawSquare(game, snakesLeft->row, snakesLeft->col);
    }
    if (food != NULL){
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        _drawSquare(game, food->row, food->col);
    }
    SDL_RenderPresent(game->renderer);
    }

int main()
{
    srand(time(NULL));
    Game game;
    Data data;
    data.sqr_size = 20;
    data.spacing = 2;
    game.data = &data;
    game.snakeGame = SnakeGame_new(20, 15);
    if (!_initWindowRenderer(&game, 438, 328))
        return 1;

    // draw background
    _drawGrid(&game);
    _render(&game, game.snakeGame->snake->head->square, NULL, game.snakeGame->firstFood);

    int lastFrameTime = 0;

    //update the game every n frames
    int i = 0;
    Input input = NONE;
    while (!game.snakeGame->gameover)
    {   
        if (i > 4){
            _updateInput(&game, &input);
            UpdatedSquares *update = _update(&game, input, &lastFrameTime);
            if (game.snakeGame->gameover) break;
            _render(&game, update->snakesMovedInto, update->snakesLeft, update->food);
            free(update);
            i = 0;
        }
        else {
            _updateInput(&game, &input);
            _pauseToFrame(&lastFrameTime);
        }
        i++;
    }

    printf("Game Over, score of %i.\n", game.snakeGame->score);
    SDL_Delay(3000);
    SnakeGame_free(game.snakeGame);
    _freeWindowRenderer(&game);
    return 0;
}

//the problem is its hitting snakes that don't get removed