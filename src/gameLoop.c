#include <stdbool.h>
#include <SDL2/SDL.h>

#include "./input.h"

typedef struct
{
    int rows;
    int cols;
    int sqr_size;
    int spacing;
} Data;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Data *data;
    bool isRunning;
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
    for (int row = 0; row <= game->data->rows; row++)
    {
        for (int col = 0; col <= game->data->cols; col++)
        {
            _drawSquare(game, row, col);
        }
    }
}

Input _process_input(Game *game)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            game->isRunning = false;
            break;
        case SDLK_w:
            return UP;
        case SDLK_UP:
            return UP;
        case SDLK_s:
            return DOWN;
        case SDLK_DOWN:
            return DOWN;
        case SDLK_d:
            return RIGHT;
        case SDLK_RIGHT:
            return RIGHT;
        case SDLK_a:
            return LEFT;
        case SDLK_LEFT:
            return LEFT;
        }
    }
    return NONE;
}


#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

void _update(Game *game, Input input, int *lastFrameTime){
    //put code here maybe?

    //ensuring constant framerate
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - *lastFrameTime);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    float delta_time = (SDL_GetTicks() - *lastFrameTime) / 1000.0;

    *lastFrameTime = SDL_GetTicks();
}

void _render(Game *game){
    SDL_RenderPresent(game->renderer);
}

int main()
{
    Game game;
    Data data;
    data.rows = 20;
    data.cols = 15;
    data.sqr_size = 20;
    data.spacing = 2;
    game.data = &data;
    game.isRunning = true;

    if (!_initWindowRenderer(&game, 438, 328))
        return 1;

    // draw background
    _drawGrid(&game);

    int lastFrameTime = 0;
    while (game.isRunning)
    {
        Input input = _process_input(&game);
        _update(&game, input, &lastFrameTime);
        _render(&game);
    }

    _freeWindowRenderer(&game);
    return 0;
}