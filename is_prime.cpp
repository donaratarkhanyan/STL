#include <iostream>

template <size_t N, size_t U>
struct is_prime_helper
{
    static const bool value = (N % U == 0) ? false : is_prime_helper<N, U - 1>::value;
};

template <size_t N>
struct is_prime_helper<N, 2>
{
    static const bool value = (N % 2);
};

template <size_t N>
struct is_prime 
{
    static const bool value = (N < 2) ? false : is_prime_helper<N, N / 2>::value;
};



int main()
{
    std::cout << is_prime<17>::value << std::endl;
}