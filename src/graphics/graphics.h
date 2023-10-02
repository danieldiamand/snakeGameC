#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>

#include "../utils/square.h"

typedef struct Color{
    int r;
    int g;
    int b;
} Color;

typedef struct Graphics{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int sqrSize;
    int spacing;
    Color background;
    Color empty;
    Color food;
    Color snake;
    Color deadSnake;
} Graphics;


Graphics *Graphics_new(int rows, int cols, int sqrSize, int spacing, Color background, Color empty, Color food, Color snake, Color deadSnake);

void Graphics_free(Graphics *graphics);

//renders update
void Graphics_render(Graphics *graphics, UpdatedSquares update);

#endif