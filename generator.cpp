#include "generator.hpp"
#include "sudoku.hpp"

#include <random>

int randomGenerator(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    int res = dist(rng);
    return res;
}

bool unUsedInBox(BoardType& board, int rowStart, int colStart, int num)
{
    for (int i = 0; i < BOX_SIZE; i++) {
        for (int j = 0; j < BOX_SIZE; j++) {
            if (board[rowStart + i][colStart + j].num == num) {
                return false;
            }
        }
    }
    return true;
}

void fillBox(BoardType& board, int row, int col)
{
    for (int i = 0; i < BOX_SIZE; i++) {
        int num;
        for (int j = 0; j < BOX_SIZE; j++) {
            do {
                num = randomGenerator(1, BOARD_SIZE);
            } while (!unUsedInBox(board, row, col, num));
            board[row + i][col + j].num = num;
        }
    }
}

void fillDiagonal(BoardType& board)
{
    for (int i = 0; i < BOARD_SIZE; i += BOX_SIZE) {
        fillBox(board, i, i);
    }
}

void markAsLocked(BoardType& board)
{
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[x][y].num)
                board[x][y].locked = true;
        }
    }
}

int deleteRandomNumbers(BoardType& board, uint8_t difficulty)
{
    int count = difficulty;
    while (count != 0) {
        int cellId = randomGenerator(0, BOARD_SIZE * BOARD_SIZE) - 1;
        int x = cellId / BOARD_SIZE;
        int y = cellId % BOARD_SIZE;
        if (board[x][y].num != 0) {
            count--;
            board[x][y].num = 0;
        }
    }
    return 0;
}

int generateBoard(BoardType& board, uint8_t difficulty)
{
    board = {};
    fillDiagonal(board);
    deleteRandomNumbers(board, difficulty);
    markAsLocked(board);

    return 0;
}