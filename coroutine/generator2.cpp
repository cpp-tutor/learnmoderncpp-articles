// generator2.cpp : unbounded generator using coroutines
// compile with: /std:c++latest (Visual Studio 2022)
//              -std=c++20 (g++)
//              -std=c++20 -stdlib=libc++ (clang++)

#include "Generator.hpp"
#include <iostream>

Generator<int> generator() {
    int i = 0;
    while (i != 6) {
        co_yield i++;
    }
    while (true) {
        co_yield i;
    }
}

int main() {
    auto gen = generator();
    for (int j = 0; j != 10; ++j) {
        std::cout << "i = " << gen() << '\n';
    }
}
