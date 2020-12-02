#include <iostream>
#include <spdlog/spdlog.h>
#include "foolsort.h"

int main()
{
    std::vector<int> a{1, 2, 3, 4, 5};
    auto result = FoolSort::quickSort(a);
    for (auto i : result)
    {
        spdlog::info("{}", i);
    }
}
