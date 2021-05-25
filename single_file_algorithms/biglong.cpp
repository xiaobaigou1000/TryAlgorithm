#include<numeric>
#include<cmath>
#include<type_traits>
#include<limits>
#include<iostream>

int main()
{
    constexpr size_t a = std::numeric_limits<int64_t>::max();
    std::cout << a;
}