#include <iostream>
#include <concepts>
#include <exception>

auto remainder(std::integral auto a, std::integral auto b) {
    return a % b;
}

auto remainder(auto a, auto b) {
    throw std::runtime_error("Bad types to remainder()");
    return -99;
}

int main() {
    std::cout << "12 % 5 = " << remainder(12, 5) << '\n';
    std::cout << "9.5 % 2.0 = " << remainder(9.5, 2.1) << '\n';
}
