#include "n_queen.h"
#include <iostream>

int main()
{
    NQueen n_queen{30};
    bool result = n_queen.calculate();
    auto board = n_queen.getBoardCopy();
    for (auto row : board)
    {
        for (auto col : row)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}
