// note: use -std=c++17 or later

#include "BigClass.hpp"
#include <iostream>

int main() {
    BigClass test( "the big data", { 1, 2, 3, 4, 5, 6 });
    auto test2 = test.clone();
    auto test3 = test;
    test.setAt(5, 100);

    auto print = [](const BigClass& b){
        std::cout << b.getName() << '\n';
        for (auto& a : b.getData()) {
            std::cout << a << ' ';
        }
        std::cout << '\n';
    };

    print(test);
    print(test2);
    print(test3);
}
