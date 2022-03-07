// cpp-range1.cpp : copy six integers from input to output 
// note: compile with -std=c++20 or /std:c++latest

#include <ranges>
#include <iostream>

using namespace std::ranges;

int main() {
    std::cout << "Type some integers:\n";
    auto pipeline = istream_view<int>(std::cin)
        | views::take(6);
    for (auto n : pipeline) {
        std::cout << n << '\n';
    }
}
