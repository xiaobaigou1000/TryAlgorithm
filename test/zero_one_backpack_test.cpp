#include "zero_one_backpack.h"
#include <iostream>
#include <cassert>

int main()
{
    auto result = backpack({{7, 10}, {5, 8}, {4, 9}}, 10);
    std::cout << result << std::endl;
    assert(result == 17);
}
