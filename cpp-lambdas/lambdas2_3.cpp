// lambdas2_3.cpp : functor with explicitly specified return type

#include <iostream>
 
template <typename U>
struct G {
    template <typename T>
    U operator()(T n) {
        return n / 2.0;
    }
};
 
int main() {
    G<double> g{};
 
    std::cout << "g(3.0): " << g(3.0) << '\n';
    std::cout << "g(3): " << g(3) << '\n';
}