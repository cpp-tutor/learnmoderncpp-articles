// consteval.cpp : demonstrate compile-time and run-time paths in constexpr function with consteval
// Note: compile with: g++ -std=c++23 consteval.cpp

#include <iostream>
 
constexpr auto f(int i) {
    return 41 + i;
}
 
constexpr int g(int i) {
    if consteval {
        return f(i);
    }
    else {
        return f(i + 1);
    }
}
 
int main() {
    const auto i = g(1);
    std::cout << "i = " << i << '\n';
    auto j = g(1);
    std::cout << "j = " << j << '\n';
}
