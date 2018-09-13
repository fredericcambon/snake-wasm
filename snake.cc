#include <iostream>
#include "snake.hh"

// https://github.com/Ace17/naarrow/tree/master/src
// https://github.com/kripken/emscripten/issues/3952

State initialState()
{
    State s = {10, 10, v2(4, 4), EAST, std::deque<v2>(), std::deque<v2>(), v2(2, 2)};

    s.snake.push_front(v2(5, 5));
    s.moves.push_back(EAST);

    return s;
}

const bool eat(State *state)
{
    return v2Eq(&state->snake[0], &state->apple);
}

const bool crash(State *state)
{
    for (int i = 1; i < state->snake.size(); i++)
    {
        if (v2Eq(&state->snake[0], &state->snake[i]))
        {
            return true;
        }
    }
    return false;
}

void updateSnake(State *state, const v2 *nextMove)
{
    // Move body
    for (int i = state->snake.size() - 1; i > 0; i--)
    {
        v2Set(&state->snake[i], &state->snake[i - 1]);
    }

    // Move head
    v2Add(&state->snake[0], nextMove);
    v2Wrap(&state->snake[0], &DIMENSIONS);
}

const bool isValidMove(const v2 *move1, const v2 *move2)
{
    return move1->x + move2->x != 0 || move1->y + move2->y != 0;
}

void enqueue(State *state, const v2 *move)
{
    if (isValidMove(&state->moves[0], move))
    {
        state->moves.push_back(*move);
    }
}

const v2 *nextMove(std::deque<v2> &moves)
{
    v2 *direction = &moves[0];

    if (moves.size() > 1)
    {
        moves.pop_front();
    }

    return direction;
}

void updateGame(State *state)
{
    if (crash(state))
    {
        state->snake.clear();
    }

    if (eat(state))
    {
        v2 newSnake = v2(state->apple.x, state->apple.y);
        state->snake.push_back(newSnake);
        v2 newApplePosition = v2(rnd(0, COLS), rnd(0, ROWS));
        v2Set(&state->apple, &newApplePosition);
    }
}

void update(State *state)
{
    updateSnake(state, nextMove(state->moves));
    updateGame(state);
}

const int x(State *state, int c)
{
    return (c % COLS) * CANVAS_WIDTH / state->cols;
}

const int y(State *state, int c)
{
    return (c % ROWS) * CANVAS_HEIGHT / state->rows;
}
