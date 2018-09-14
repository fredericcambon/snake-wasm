#include <SDL2/SDL.h>
#include "snake.hh"

/**
 * Main struct for web snake, handles SDL display and
 * game state
 */
struct context
{
    SDL_Renderer *renderer;
    State *state;
};
