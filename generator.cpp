#include "generator.hpp"
#include "sudoku.hpp"

#include <random>

int randomGenerator(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
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
    int num;
    for (int i = 0; i < BOX_SIZE; i++) {
        for (int j = 0; j < BOX_SIZE; j++) {
            do {
                num = randomGenerator(1,BOARD_SIZE);
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

int generateBoard(BoardType& board)
{

    fillDiagonal(board);

    // TODO: delete random numbers

    markAsLocked(board);

    return 0;
}