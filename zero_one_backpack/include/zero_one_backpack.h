#include <vector>
#include <tuple>
#include <algorithm>

int64_t backpack(const std::vector<std::tuple<int64_t, int64_t>> &items, const int64_t maxSize)
{
    std::vector<int64_t> values(maxSize + 1);

    for (const auto [weight, value] : items)
    {
        for (int64_t packSize = maxSize; packSize >= weight; packSize--)
        {
            values[packSize] = std::max(values[packSize - weight] + value, values[packSize]);
        }
    }
    return values.back();
}
