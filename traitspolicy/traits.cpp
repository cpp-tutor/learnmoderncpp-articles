#include "Traits.hpp"
#include <iostream>
#include <initializer_list>

template<typename T, typename R = AccumulateTypeTraits<T>::Type>
auto accum(const std::initializer_list<T>& arr) {
    R r{};
    auto elem = arr.begin(), end = arr.end();
    while (elem != end) {
        r += *elem++;
    }
    return r;
}

int main() {
    std::cout << "accum({1, 2, 3, 4, 5}) = " << accum({1, 2, 3, 4, 5}) << '\n';
    std::cout << "accum({'a', 'b', 'c', 'd', 'e'}) = " << accum({'a', 'b', 'c', 'd', 'e'}) << '\n';
    std::cout << "accum({1.1, 2.2, 3.3, 4.4, 5.5}) = " << accum({1.1, 2.2, 3.3, 4.4, 5.5}) << '\n';
}
