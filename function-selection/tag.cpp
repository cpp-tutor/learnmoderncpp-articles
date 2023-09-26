#include <iostream>
#include <cmath>
 
class Integral{};
 
class Floating{};
 
int index(Integral, int x, unsigned p) {
    if (p == 0) {
        std::cerr << "index(Integral)\n";
        return 1;
    }
    else {
        return x * index(Integral{}, x, p - 1);
    }
}
 
double index(Floating, double x, unsigned p) {
    std::cerr << "index(Floating)\n";
    return pow(x, static_cast<double>(p));
}
 
int main() {
    auto a = index(Integral{}, -3, 4);
    std::cout << "(-3) ^ 4 = " << a << '\n';
    auto b = index(Floating{}, 2.5, 2);
    std::cout << "2.5 ^ 2 = " << b << '\n';
}
