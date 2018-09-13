#include <SDL2/SDL.h>
#include "snake.hh"

struct context
{
    SDL_Renderer *renderer;
    State *state;
};
