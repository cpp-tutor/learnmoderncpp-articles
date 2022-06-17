// lambdas2_1.cpp : lambda with generic parameter

#include <iostream>
 
int main() {
    auto g = [](auto n){ return n / 2; };
 
    std::cout << "g(3.0): " << g(3.0) << '\n';
    std::cout << "g(3): " << g(3) << '\n';
}