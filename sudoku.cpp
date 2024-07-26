#include "sudoku.hpp"
#include "generator.hpp"

#include <set>

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

bool isValid(BoardType& board)
{
    // Check horizontally
    for (uint8_t y = 0; y < BOARD_SIZE; y++) {
        std::set<int> row = {};

        for (uint8_t x = 0; x < BOARD_SIZE; x++) {
            auto num = board[x][y].num;

            // 0 check is done here because its the first step and checking again somewhere else is useless
            if (num == 0)
                return false;

            if (row.insert(num).second == false)
                return false;
        }
    }

    // Check vertically
    for (uint8_t x = 0; x < BOARD_SIZE; x++) {
        std::set<int> column = {};

        for (uint8_t y = 0; y < BOARD_SIZE; y++) {
            auto num = board[x][y].num;

            if (column.insert(num).second == false)
                return false;
        }
    }

    // Check box
    for (uint8_t x = 1; x < BOARD_SIZE; x += BOX_SIZE) {
        for (uint8_t y = 1; y < BOARD_SIZE; y += BOX_SIZE) {
            std::set<int> box;
            if (box.insert(board[x - 1][y - 1].num).second == false)
                return false;
            if (box.insert(board[x][y - 1].num).second == false)
                return false;
            if (box.insert(board[x + 1][y - 1].num).second == false)
                return false;

            if (box.insert(board[x - 1][y].num).second == false)
                return false;
            if (box.insert(board[x][y].num).second == false)
                return false;
            if (box.insert(board[x + 1][y].num).second == false)
                return false;

            if (box.insert(board[x - 1][y + 1].num).second == false)
                return false;
            if (box.insert(board[x][y + 1].num).second == false)
                return false;
            if (box.insert(board[x + 1][y + 1].num).second == false)
                return false;
        }
    }

    return true;
}

int main(int, char**)
{
    BoardType board = {};

    Selected sel = { 0, 0, 1 };

    initscr();
    start_color();

    /*
        Available colors:
        COLOR_BLACK
        COLOR_RED
        COLOR_GREEN
        COLOR_YELLOW
        COLOR_BLUE
        COLOR_MAGENTA
        COLOR_CYAN
        COLOR_WHITE
    */

    // (number/name, foreground, background)
    init_pair(COL_SELECTED, COLOR_BLACK, COLOR_CYAN);
    init_pair(COL_SAME_SEL_NUM, COLOR_BLACK, COLOR_RED);
    init_pair(COL_SAME_SEL_AXIS, COLOR_CYAN, COLOR_BLACK);

    generateBoard(board);

    setbuf(stdout, NULL);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (true) {
        clear(); // Clear console
        printBoard(board, sel);
        printw("\n");
        printw("\n");
        printSelDialog(sel);
        refresh(); // Flush
        int ch = -1;
        while (ch == -1) {
            ch = getch();
        }
        switch (ch) {
            case KEY_UP: // Up
                if (sel.y)
                    sel.y--;
                break;
            case KEY_DOWN: // Down
                if (sel.y < BOARD_SIZE - 1)
                    sel.y++;
                break;
            case KEY_LEFT: // Right
                if (sel.x)
                    sel.x--;
                break;
            case KEY_RIGHT: // Left
                if (sel.x < BOARD_SIZE - 1)
                    sel.x++;
                break;

            case '1':
                sel.num = 1;
                break;
            case '2':
                sel.num = 2;
                break;
            case '3':
                sel.num = 3;
                break;
            case '4':
                sel.num = 4;
                break;
            case '5':
                sel.num = 5;
                break;
            case '6':
                sel.num = 6;
                break;
            case '7':
                sel.num = 7;
                break;
            case '8':
                sel.num = 8;
                break;
            case '9':
                sel.num = 9;
                break;

            case KEY_ENTER:
            case ' ':
            case '\n':
                if (board[sel.x][sel.y].locked)
                    break;
                board[sel.x][sel.y].num = sel.num;
                break;

            case KEY_BACKSPACE:
                if (board[sel.x][sel.y].locked)
                    break;

                board[sel.x][sel.y].num = 0;
                break;
        }
        auto valid = isValid(board);
        if (valid)
            break;
    }

    return 0;
}
