// lambdas2_2.cpp : lambdas2_1.cpp rewitten as a functor

#include <iostream>
 
struct G {
    template <typename T>
    T operator()(T n) {
        return n / 2;
    }
};
 
int main() {
    G g{};
 
    std::cout << "g(3.0): " << g(3.0) << '\n';
    std::cout << "g(3): " << g(3) << '\n';
}