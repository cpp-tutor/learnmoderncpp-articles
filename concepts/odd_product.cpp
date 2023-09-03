#include "is_positive.hpp"
#include "is_odd.hpp"
#include <type_traits>
#include <iostream>

template<typename T, T N>
concept counting_odd =
    std::is_integral_v<T>
    && is_positive<T,N>()
    && is_odd_v<N>;

template<typename T, T N, T M>
requires counting_odd<T, N> && counting_odd<T, M>
constexpr T odd_multiply() {
    return N * M;
}

int main() {
    std::cout << "3 times 5 is an odd number: " << odd_multiply<unsigned, 3, 5>() << '\n';
    std::cout << "7 times 13 is an odd number: " << odd_multiply<int, 7, 13>() << '\n';
    //odd_multiply<int, -3, 5>();
    //odd_multiply<int, 3, 6>();
    //odd_multiply<double, 3.0, 5.0>();
}
