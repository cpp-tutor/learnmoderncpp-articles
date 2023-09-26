#include <iostream>
#include <cmath>
 
int index(int x, unsigned p) {
    if (p == 0) {
        std::cerr << "index(int, unsigned)\n";
        return 1;
    }
    else {
        return x * index(x, p - 1);
    }
}
 
double index(double x, unsigned p) {
    std::cerr << "index(double, unsigned)\n";
    return pow(x, static_cast<double>(p));
}
 
int index(...) {
    std::cerr << "index(...)\n";
    return 0;
}
 
int main() {
    auto a = index(-3, 4);
    std::cout << "(-3) ^ 4 = " << a << '\n';
    auto b = index(2.5, 2);
    std::cout << "2.5 ^ 2 = " << b << '\n';
    auto c = index("Hello", "There");
    std::cout << c << '\n';
}
