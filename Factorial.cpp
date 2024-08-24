#include <iostream>

template <size_t N>
struct fac
{
    static const size_t value = N * fac<N - 1>::value;
};

template <>
struct fac<1>
{
    static const size_t value = 1;
};

int main()
{
    std::cout << fac<5>::value;  
}