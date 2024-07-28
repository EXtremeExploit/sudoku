#include "sudoku.hpp"
#include "generator.hpp"
#include "prints.hpp"
#include "util.hpp"
#include "validator.hpp"

#include <pwd.h>
#include <unistd.h>

std::string getConfigDir()
{
    struct passwd* pw = getpwuid(getuid());
    char* XDG_CONFIG_HOME = getenv("XDG_CONFIG_HOME");
    std::string pw_dir = std::string(pw->pw_dir);
    std::string configPath = pw_dir + ".config/sudoku";

    if (XDG_CONFIG_HOME != nullptr) {
        std::string configDir = std::string(XDG_CONFIG_HOME);
        configPath = configDir + "/sudoku";
    }

    return configPath;
}

int main(int argc, char** argv)
{
    initscr();
    start_color();

    const auto configDir = getConfigDir();
    const auto configPath = configDir + "/config.cfg";

    uint8_t difficulty = 10;
    uint8_t startX = 0;
    uint8_t startY = 0;
    uint8_t startNum = 1;

    auto f = fopen(configPath.c_str(), "r");
    if (f) {
        char currentLine[128] = {};
        while (fgets(currentLine, sizeof(currentLine), f) != NULL) {
            const std::string untrimmedLine(currentLine);

            const std::string uncommentedline = trim(untrimmedLine);

            const std::string line = uncommentedline.substr(0, uncommentedline.find_first_of('#'));

            if (line.starts_with("difficulty")) {
                auto valueString = line.substr(line.find_last_of(" "), std::string::npos);
                auto value = std::max(0, std::min(std::stoi(valueString), 27));
                difficulty = value;
            }
            if (line.starts_with("startX")) {
                auto valueString = line.substr(line.find_last_of(" "), std::string::npos);
                auto value = std::max(0, std::min(std::stoi(valueString), BOARD_SIZE - 1));
                startX = value;
            }
            if (line.starts_with("startY")) {
                auto valueString = line.substr(line.find_last_of(" "), std::string::npos);
                auto value = std::max(0, std::min(std::stoi(valueString), BOARD_SIZE - 1));
                startY = value;
            }
            if (line.starts_with("startNum")) {
                auto valueString = line.substr(line.find_last_of(" "), std::string::npos);
                auto value = std::max(1, std::min(std::stoi(valueString), BOARD_SIZE));
                startNum = value;
            }
        }
    }

    Selected sel = {
        startX,
        startY,
        startNum
    };

    BoardType board = {};
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

    generateBoard(board, difficulty);

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
            case KEY_UP:
            case 'w':
                if (sel.y)
                    sel.y--;
                break;
            case KEY_DOWN:
            case 's':
                if (sel.y < BOARD_SIZE - 1)
                    sel.y++;
                break;
            case KEY_LEFT:
            case 'a':
                if (sel.x)
                    sel.x--;
                break;
            case KEY_RIGHT:
            case 'd':
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

            case 'q':
                sel.num = std::min(std::max(1, sel.num - 1), BOARD_SIZE);
                break;
            case 'e':
                sel.num = std::min(std::max(1, sel.num + 1), BOARD_SIZE);
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

            case 'r':
                generateBoard(board, difficulty);

                sel = {
                    startX,
                    startY,
                    startNum
                };

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
