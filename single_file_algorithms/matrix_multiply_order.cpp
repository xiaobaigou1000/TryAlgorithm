#include<spdlog/spdlog.h>
#include<vector>
#include<tuple>
#include<random>

#include <iostream>
#include <future>
#include <thread>
#include <numeric>
#include <cmath>
#include <functional>

size_t getMultiplyTimes(std::tuple<size_t, size_t> lhd, std::tuple<size_t, size_t> rhd)
{
    assert(std::get<1>(lhd) == std::get<0>(rhd));
    return std::get<0>(lhd) * std::get<1>(rhd) * std::get<1>(lhd);
}

template<typename Iter>
size_t minimumMultiplyTimes(Iter begin, Iter end)
{
    using ValueType = std::iterator_traits<Iter>::value_type;
    size_t matrixNum = end - begin;
    std::vector dpTable(matrixNum, std::vector<size_t>(matrixNum, 0));
    for (size_t i = 0; i < matrixNum; i++)
    {
        for (size_t j = i; j < matrixNum; j++)
        {
        }
    }
}

int main()
{
    std::vector<std::tuple<size_t, size_t>> matrixSize{ {50,10},{10,40},{40,30},{30,5} };

    std::normal_distribution<double> nd(5, 1);
    std::mt19937_64 randomEngine(std::random_device{}());

    std::packaged_task<int(int, int)> task([](int a, int b) {
        return std::pow(a, b);
        });

    std::cout << task.valid() << std::endl;

    std::future<int> result = task.get_future();

    try
    {
        std::cout << task.valid() << std::endl;
        task(2, 2);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        std::cout << task.valid() << std::endl;
        std::cout << "task_lambda:\t" << result.get() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}