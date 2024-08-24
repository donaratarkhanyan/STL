#include <iostream>

template <size_t N>
struct fib {
    static const size_t value = fib<N - 1>::value + fib<N - 2>::value;
};

template <>
struct fib<0> {
    static const size_t value = 0;
};

template <>
struct fib<1> {
    static const size_t value = 1;
};

int main()
{
    std::cout << fib<8>::value;   
    return 0;
}