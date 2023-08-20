#include "Traits.hpp"
#include "Policy.hpp"
#include <iostream>
#include <initializer_list>

template<typename P = SummationPolicy, typename T = void, typename R = AccumulateTypeTraits<T>::Type>
auto accum(const std::initializer_list<T>& arr) {
    R r{ P::init };
    auto elem = arr.begin(), end = arr.end();
    while (elem != end) {
        P::operation(r, *elem++);
    }
    return r;
}

int main() {
    std::cout << "accum({1, 2, 3, 4, 5}) = " << accum({1, 2, 3, 4, 5}) << '\n';
    std::cout << "accum({'a', 'b', 'c', 'd', 'e'}) = " << accum({'a', 'b', 'c', 'd', 'e'}) << '\n';
    std::cout << "accum({1.1, 2.2, 3.3, 4.4, 5.5}) = " << accum({1.1, 2.2, 3.3, 4.4, 5.5}) << '\n';
    std::cout << "accum<MultiplicationPolicy>({1, 2, 3, 4, 5}) = " << accum<MultiplicationPolicy>({1, 2, 3, 4, 5}) << '\n';
    std::cout << "accum<MultiplicationPolicy>({'a', 'b', 'c', 'd', 'e'}) = " << accum<MultiplicationPolicy>({'a', 'b', 'c', 'd', 'e'}) << '\n';
    std::cout << "accum<MultiplicationPolicy>({1.1, 2.2, 3.3, 4.4, 5.5}) = " << accum<MultiplicationPolicy>({1.1, 2.2, 3.3, 4.4, 5.5}) << '\n';
}
