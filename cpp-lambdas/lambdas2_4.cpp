// lambdas2_4.cpp : functor with implicit return type

#include <iostream>
 
struct G {
    template <typename T>
    auto operator()(T n) {
        double r = n / 2.0;
        return r;
    }
};
 
int main() {
    G g{};
 
    std::cout << "g(3.0): " << g(3.0) << '\n';
    std::cout << "g(3): " << g(3) << '\n';
}