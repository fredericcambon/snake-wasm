#include <iostream>
#include <deque>

struct v2
{
    v2(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    int x;
    int y;
};

struct State
{
    std::deque<v2> moves;
    std::deque<v2> snake;
    v2 apple;
};

static const int COLS = 10;
static const int ROWS = 10;
static const v2 DIMENSIONS = v2(COLS, ROWS);
static const int CANVAS_WIDTH = 500;
static const int CANVAS_HEIGHT = 500;
static const v2 NORTH = v2(0, -1);
static const v2 SOUTH = v2(0, 1);
static const v2 WEST = v2(-1, 0);
static const v2 EAST = v2(1, 0);

// Base lib
const bool v2Eq(const v2 *, const v2 *);
void v2Add(v2 *, const v2 *);
void v2Set(v2 *, const v2 *);
void v2Wrap(v2 *, const v2 *);
int rnd(int, int);
int mod(int, int);

const int x(State *, int);
const int y(State *, int);

void enqueue(State *, const v2 *);
void update(State *);

State initialState();
