#include "sudoku.hpp"

int printBoard(BoardType& board, Selected& sel)
{
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (x % BOX_SIZE == 0 && x != 0) {
                printw(" | ");
            }
            if (y % BOX_SIZE == 0 && y != 0 && x == 0) {
                printw("----- | ----- | -----\n");
            }

            uint8_t num = board[x][y].num;

            uint8_t color = 0;

            if (x == sel.x || y == sel.y)
                color = COL_SAME_SEL_AXIS;
            if (sel.num == num)
                color = COL_SAME_SEL_NUM;
            if (sel.x == x && sel.y == y)
                color = COL_SELECTED;

            if (color)
                attron(COLOR_PAIR(color));

            if (board[x][y].locked) {
                attron(A_BOLD);
            }

            char num_str = num ? '0' + num : ' ';
            printw("%c", num_str);

            if (color)
                attroff(COLOR_PAIR(color));

            if (board[x][y].locked) {
                attroff(A_BOLD);
            }

            if (x == BOARD_SIZE - 1)
                continue;

            if (x == 0 || (x + 1) % BOX_SIZE != 0)
                printw("|");
        }
        printw("\n");
    }

    return 0;
}

int printSelDialog(Selected& sel)
{
    for (int i = 1; i <= BOARD_SIZE; i++) {

        if (sel.num == i)
            attron(COLOR_PAIR(COL_SELECTED));

        printw("%d", i);

        if (sel.num == i)
            attroff(COLOR_PAIR(COL_SELECTED));
        printw(" ");
    }
    return 0;
}