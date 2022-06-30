// generator1.cpp : simple generator using coroutines
// compile with: /std:c++latest (Visual Studio 2022)
//              -std=c++20 (g++)
//              -std=c++20 -stdlib=libc++ (clang++)

#include "Generator.hpp"
#include <iostream>

Generator<int> generator() {
    for (int i = 0; i != 3; ++i) {
        co_yield i;
    }
}

int main() {
    auto gen = generator();
    while (gen) {
        std::cout << "i = " << gen() << '\n';
    }
}
