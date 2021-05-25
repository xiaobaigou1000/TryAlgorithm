#include<spdlog/spdlog.h>
#include<vector>
#include<algorithm>

template<typename Iter>
Iter my_binary_search(Iter begin, Iter end, typename std::iterator_traits<Iter>::value_type toSearch)
{
    using ValueType = std::iterator_traits<Iter>::value_type;

    while (begin != (end - 1))
    {
        Iter middle = begin + (end - begin) / 2;
        if (toSearch == *middle) return middle;
        if (toSearch < *middle)
            end = middle;
        else
            begin = middle;
    }
    return end;
}

int main()
{
    std::vector a{ 1,3,4,5 };
    auto i = my_binary_search(a.begin(), a.end(), 2);
    spdlog::info("search result: {}", *i);
}
