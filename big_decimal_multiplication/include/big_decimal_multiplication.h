#include <boost/multiprecision/cpp_int.hpp>
#include <numeric>

using MyBigInt = boost::multiprecision::cpp_int;

MyBigInt unsafe_multiply(MyBigInt l, MyBigInt r, int n)
{
    if (n == 1)
    {
        return l * r;
    }
    if (l == 0 || r == 0)
    {
        return 0;
    }
    int m = n / 2;
    MyBigInt x1 = l / MyBigInt(std::pow(10, m));
    MyBigInt x0 = l - x1 * MyBigInt(std::pow(10, m));
    MyBigInt y1 = r / MyBigInt(std::pow(10, m));
    MyBigInt y0 = r - y1 * MyBigInt(std::pow(10, m));

    MyBigInt z2 = unsafe_multiply(x1, y1, m);
    MyBigInt z0 = unsafe_multiply(x0, y0, m);
    MyBigInt z1 = unsafe_multiply((x0 - x1), (y1 - y0), m) + z2 + z0;
    return z2 * MyBigInt(std::pow(10, 2 * m)) + z1 * MyBigInt(std::pow(10, m)) + z0;
}

MyBigInt multiply(MyBigInt l, MyBigInt r, int n)
{
    if (n % 2 == 1)
    {
        n += 1;
    }
    return unsafe_multiply(l, r, n);
}

size_t calculateBase2Digits(MyBigInt num)
{
    size_t digits = 0;
    while (!num.is_zero())
    {
        digits += 1;
        num >>= 1;
    }
    return digits;
}

MyBigInt unsafe_base2_multiply(MyBigInt l, MyBigInt r, size_t n)
{
    if (n == 1)
    {
        return l * r;
    }
    if (l.is_zero() || r.is_zero())
    {
        return 0;
    }
    size_t m = (n + 1) / 2;

    MyBigInt x1 = l >> m;
    MyBigInt x0 = l - (x1 << m);
    MyBigInt y1 = r >> m;
    MyBigInt y0 = r - (y1 << m);

    MyBigInt z2 = unsafe_base2_multiply(x1, y1, m);
    MyBigInt z0 = unsafe_base2_multiply(x0, y0, m);
    MyBigInt z1 = unsafe_base2_multiply((x0 - x1), (y1 - y0), m) + z2 + z0;
    return ((z2 << (2 * m)) + (z1 << m) + z0);
}

MyBigInt base2_multiply(MyBigInt l, MyBigInt r)
{
    size_t n = std::max(calculateBase2Digits(l), calculateBase2Digits(r));
    return unsafe_base2_multiply(l, r, n);
}