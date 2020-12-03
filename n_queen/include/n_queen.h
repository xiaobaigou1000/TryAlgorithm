#pragma once
#include <vector>

class NQueen
{
public:
    NQueen() : board(boardSize, std::vector<int32_t>(boardSize, 0)) {}

    bool calculate()
    {
        return findQueen(0);
    }

    bool findQueen(int64_t row)
    {
        if (row >= boardSize)
        {
            return true;
        }

        for (int64_t col = 0; col < boardSize; col++)
        {
            if (checkValid(row, col))
            {
                board[row][col] = 1;
                bool result = findQueen(row + 1);
                if (result == false)
                {
                    board[row][col] = 0;
                }
                else
                {
                    return true;
                }
            }
        }
        return false;
    }

    std::vector<std::vector<int32_t>> getBoardCopy()
    {
        return board;
    }

private:
    std::vector<std::vector<int32_t>> board;
    static constexpr int64_t boardSize = 8;
    bool checkValid(int64_t row, int64_t col)
    {
        bool val = true;
        for (int64_t currentRow = row - 1, leftCol = col - 1, rightCol = col + 1; currentRow >= 0; --currentRow, --leftCol, ++rightCol)
        {
            if (leftCol >= 0)
            {
                if (board[currentRow][leftCol] != 0)
                {
                    val = false;
                    break;
                }
            }

            if (rightCol < boardSize)
            {
                if (board[currentRow][rightCol] != 0)
                {
                    val = false;
                    break;
                }
            }

            if (board[currentRow][col] != 0)
            {
                val = false;
                break;
            }
        }
        return val;
    }
};