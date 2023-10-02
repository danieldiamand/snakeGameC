#include "graphics.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../utils/square.h"

void _Graphics_setColor(Graphics *graphics, Color color){
    SDL_SetRenderDrawColor(graphics->renderer, color.r, color.g, color.b, 255);
}

void _Graphics_drawSquare(Graphics *graphics, int row, int col)
{
    SDL_Rect rect = {row * (graphics->sqrSize + graphics->spacing), col * (graphics->sqrSize + graphics->spacing), graphics->sqrSize , graphics->sqrSize};
    SDL_RenderFillRect(graphics->renderer, &rect);
}

void _Graphics_drawBackground(Graphics *graphics, int rows, int cols){
    _Graphics_setColor(graphics, graphics->background);
    SDL_RenderClear(graphics->renderer);
    _Graphics_setColor(graphics, graphics->empty);
    for (int row = 0; row <= rows; row++)
    {
        for (int col = 0; col <= cols; col++)
        {
            _Graphics_drawSquare(graphics, row, col);
        }
    }
}

Graphics *Graphics_new(int rows, int cols, int sqrSize, int spacing, Color background, Color empty, Color food, Color snake, Color deadSnake)
{
    Graphics *graphics = malloc(sizeof(graphics));

    graphics -> sqrSize = sqrSize;
    graphics -> spacing = spacing;
    graphics -> background = background;
    graphics -> empty = empty;
    graphics -> food = food;
    graphics -> snake = snake;
    graphics -> deadSnake = deadSnake;

    const int width = rows * sqrSize + (rows - 1) * spacing;
    const int height = cols * sqrSize + (cols - 1) * spacing;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        exit(1);
    }

    graphics->window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN // not sure about which thing i should use here
    );

    if (!graphics->window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        exit(1);
    }

    graphics->renderer = SDL_CreateRenderer(graphics->window, -1, 0);
    if (!graphics->renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        exit(1);
    }

    _Graphics_drawBackground(graphics, rows, cols);
    return graphics;
}

void Graphics_free(Graphics *graphics){
    SDL_DestroyRenderer(graphics->renderer);
    SDL_DestroyWindow(graphics->window);
    free(graphics);
    SDL_Quit();
}

void Graphics_render(Graphics *graphics, UpdatedSquares update){
    _Graphics_setColor(graphics, graphics->snake);
    _Graphics_drawSquare(graphics, update.snakesMovedInto.row, update.snakesMovedInto.col);

    if (update.snakeGrown){
        _Graphics_setColor(graphics, graphics->food);
        _Graphics_drawSquare(graphics, update.food.row, update.food.col);
    }else{
         _Graphics_setColor(graphics, graphics->empty);
        _Graphics_drawSquare(graphics, update.snakesMovedOut.row, update.snakesMovedOut.col);
    }

    SDL_RenderPresent(graphics->renderer);
}

