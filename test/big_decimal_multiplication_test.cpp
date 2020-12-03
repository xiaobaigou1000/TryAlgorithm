#include "big_decimal_multiplication.h"
#include <cassert>

int main()
{
    boost::multiprecision::cpp_int a("5");
    boost::multiprecision::cpp_int b("7");
    auto result = base2_multiply(a, b);
    assert(result == boost::multiprecision::cpp_int("35"));
}