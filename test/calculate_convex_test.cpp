#include "calculate_convex.h"
#include <iostream>

int main()
{
    std::vector<glm::vec2> vec{{0, 0}, {4, 0}, {1, 4}, {1, -4}, {1, 3}, {2, -4}};
    auto result = calculate_convex::calculate2DConvex(vec);

    for (auto i : result)
    {
        std::cout << "x = " << i.x << ", y = " << i.y << std::endl;
    }
    assert(static_cast<int>(result[0].x)==0);
    assert(static_cast<int>(result[0].y)==0);

    assert(static_cast<int>(result[1].x)==1);
    assert(static_cast<int>(result[1].y)==4);

    assert(static_cast<int>(result[2].x)==4);
    assert(static_cast<int>(result[2].y)==0);
}