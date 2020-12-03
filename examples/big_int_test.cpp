#include "big_decimal_multiplication.h"
#include "complexity_tool.h"
#include <random>
#include <cstring>

using MyBigInt = boost::multiprecision::cpp_int;

int main()
{
    try
    {

        std::random_device rd;

        auto random_cpp_int = [&rd](size_t data_len) {
            std::vector<char> buffer(data_len + 1);
            buffer[0]='2';
            size_t i;
            for (i = 1; i < data_len; i++)
            {
                auto rdval = rd();
                char a = '0' + (rdval % 10);
                buffer[i] = a;
            }
            buffer[i] = 0;
            // std::cout << buffer.data() << std::endl;
            return MyBigInt{buffer.data()};
        };

        std::cout<<"size,time,mem\n";

        const size_t step = 5000;
        const size_t repeat_times = 100;
        const size_t initial_size = 50000;

        for (size_t data_len = initial_size; data_len < initial_size + repeat_times * step; data_len += step)
        {
            ComplexityMeasurement cm;

            cm.run();
            auto x = random_cpp_int(data_len);
            auto y = random_cpp_int(data_len);
            auto result = x*y;
            cm.stop();
            std::cout << data_len << ',';

            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(cm.getPassedTime()).count() << ",";
            std::cout << cm.getMemoryUsage() << std::endl;
            // std::cout << result << std::endl;
        }
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
}
