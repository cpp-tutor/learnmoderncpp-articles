// cpp-range4.cpp : test the distribution of random number generator
// note: compile with -std=c++17 or /std:c++20

#include <range/v3/view.hpp>
#include <random>
#include <vector>
#include <iostream>

using namespace ranges::v3;

int main() {
    std::mt19937 my_rand(0);
    auto pipeline = views::generate(my_rand)
        | views::take(1'000'000)
        | views::filter([](auto n){ return (n % 101) == 0; })
        | to<std::vector>();
    std::cout << "Expected: " << 1'000'000 / 101 << ", got: " << pipeline.size() << '\n';
}
