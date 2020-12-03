#include "find_lis.h"
#include <iostream>
#include <cassert>

int main()
{
    std::vector<int> seq{1, 2, 3, 4, 4, 5, 2, 3, 4, 5, 6, 7, 8, 0, 9, -1, 100};
    auto result = findLIS(seq.begin(), seq.end());
    for (const int i : result)
    {
        std::cout << i << std::endl;
    }
    assert(result[0] == 1);
    assert(result[3] == 4);
}