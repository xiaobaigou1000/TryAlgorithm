#include "n_queen.h"
#include "complexity_tool.h"
#include <iostream>

int main()
{
    for (int64_t i = 8; i < 30; i++)
    {
        std::cout << "current board size: " << i << std::endl;
        ComplexityMeasurement cm;
        cm.run();

        NQueen n_queen{i};
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

        cm.stop();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(cm.getPassedTime()).count() << std::endl;
        std::cout << cm.getMemoryUsage() << std::endl;
    }
}
