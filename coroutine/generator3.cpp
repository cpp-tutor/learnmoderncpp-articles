// generator3.cpp : factorial generator using coroutines
// compile with: /std:c++latest (Visual Studio 2022)
//              -std=c++20 (g++)
//              -std=c++20 -stdlib=libc++ (clang++)

#include "Generator.hpp"
#include <iostream>

Generator<int> generator(unsigned n) {
    if (n == 0) {
        co_return;
    }
    int f = 1;
    co_yield f;
    for (int i = 1; i != n; ++i) {
        co_yield f *= i;
    }
}

int main() {
    auto gen = generator(10);
    for (int i = 0; gen; ++i) {
        std::cout << i << "! = " << gen() << '\n';
    }
}
