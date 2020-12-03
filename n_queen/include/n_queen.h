#pragma once
#include <vector>

class NQueen
{
public:
    NQueen() : board(boardSize, std::vector<int32_t>(boardSize, 0)) {}

private:
    std::vector<std::vector<int32_t>> board;
    static constexpr size_t boardSize = 8;
    bool checkValid(size_t row, size_t col)
    {
        bool val = true;
        if (board[row][col] != 0)
        {
            val = false;
        }
        for (size_t i = 0; i < col; i++)
        {

        }
    }
}