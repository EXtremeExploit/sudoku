#include "sudoku.hpp"
#include "generator.hpp"
#include "prints.hpp"
#include "validator.hpp"

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
        bool boardChanged = false;
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
                boardChanged = true;
                break;

            case KEY_BACKSPACE:
            case '0':
                if (board[sel.x][sel.y].locked)
                    break;

                board[sel.x][sel.y].num = 0;
                boardChanged = true;
                break;
        }

        if (boardChanged) {
            auto valid = isValid(board);
            if (valid)
                break;
        }
    }

    return 0;
}
