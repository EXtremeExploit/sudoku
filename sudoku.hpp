#pragma once

#include <array>
#include <cmath>
#include <ncurses.h>

#define BOARD_SIZE 9
const int BOX_SIZE = std::sqrt(BOARD_SIZE);
#define EMPTY 0

typedef struct Cell {
    uint8_t num;
    bool locked;
} Cell;

typedef std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE> BoardType;

typedef struct Selected {
    uint8_t x;
    uint8_t y;
    uint8_t num;
} Selected;

#define COL_SELECTED 1
#define COL_SAME_SEL_NUM 2
#define COL_SAME_SEL_AXIS 3
