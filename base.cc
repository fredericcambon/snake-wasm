#include <iostream>
#include <vector>
#include "snake.hh"

int rnd(int min, int max)
{
    return rand() % max + min;
}

int mod(int y, int x)
{
    // Special mod function to handle negative numbers
    return (x + (y % x)) % x;
}

const bool v2Eq(const v2 *a, const v2 *b)
{
    return a->x == b->x && a->y == b->y;
}

void v2Add(v2 *a, const v2 *b)
{
    a->x = a->x + b->x;
    a->y = a->y + b->y;
}

void v2Set(v2 *a, const v2 *b)
{
    a->x = b->x;
    a->y = b->y;
}

void v2Wrap(v2 *a, const v2 *b)
{
    a->x = mod(a->x, b->x);
    a->y = mod(a->y, b->y);
}
