// cpp-range2.cpp : print first ten multiples of 13
// note: compile with -std=c++20 or /std:c++latest

#include <ranges>
#include <iostream>

using namespace std::ranges;

int main() {
    auto pipeline = views::iota(1)
        | views::transform([](int n){ return n * 13; })
        | views::take(10);
    for (auto n : pipeline) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
