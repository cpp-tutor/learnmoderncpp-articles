#include "pyrange.hpp"
#include <iostream>

int main() {
    for (auto a : pyrange(10)) {
        std::cout << a << ' ';
    } // 0 1 2 3 4 5 6 7 8 9
    std::cout << '\n';

    for (auto b : pyrange(19, -19, -2)) {
        std::cout << b << ' ';
    } // 19 17 15 13 11 9 7 5 3 1 -1 -3 -5 -7 -9 -11 -13 -15 -17
    std::cout << '\n';

    for (auto c : pyrange(-10, 10, -1)) {
        std::cout << c << ' ';
    } // no output

    for (auto d : pyrange(0, 10, 0)) {
        std::cout << d << ' ';
    } // execption thrown
}
