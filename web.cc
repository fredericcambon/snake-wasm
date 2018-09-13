#include <SDL2/SDL.h>
#include <emscripten.h>
#include "web.hh"

void input(context *ctx)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        /* Look for a keypress */
        case SDL_KEYDOWN:
            /* Check the SDLKey values and move change the coords */
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                enqueue(ctx->state, &WEST);
                break;
            case SDLK_RIGHT:
                enqueue(ctx->state, &EAST);
                break;
            case SDLK_UP:
                enqueue(ctx->state, &NORTH);
                break;
            case SDLK_DOWN:
                enqueue(ctx->state, &SOUTH);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void drawRect(context *ctx, v2 *pos, int r, int g, int b)
{
    SDL_Rect rect;

    SDL_SetRenderDrawColor(ctx->renderer, r, g, b, 255);
    rect.x = x(ctx->state, pos->x);
    rect.y = y(ctx->state, pos->y);
    rect.w = 50;
    rect.h = 50;
    SDL_RenderFillRect(ctx->renderer, &rect);
}

void draw(context *ctx)
{
    if (ctx->state->snake.size() == 0)
    {
        SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    }

    SDL_RenderClear(ctx->renderer);

    // Draw apple
    drawRect(ctx, &ctx->state->apple, 255, 0, 0);

    // Draw snake
    for (int i = 0; i < ctx->state->snake.size(); i++)
    {
        drawRect(ctx, &ctx->state->snake[i], 0, 255, 0);
    }

    SDL_RenderPresent(ctx->renderer);
}

void mainloop(void *arg)
{
    context *ctx = static_cast<context *>(arg);

    input(ctx);
    update(ctx->state);
    draw(ctx);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    State state = initialState();

    SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window, &renderer);

    context ctx = {renderer, &state};

    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = 10;                   // call the function as fast as the browser wants to render (typically 60fps)
    emscripten_set_main_loop_arg(mainloop, &ctx, fps, simulate_infinite_loop);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}