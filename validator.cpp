#include "sudoku.hpp"

#include <set>

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
