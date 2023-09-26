#include <iostream>
#include <cmath>
 
template<typename T>
T index(T x, unsigned p) {
    if (p == 0) {
        std::cerr << "index<T>()\n";
        return 1;
    }
    else {
        return x * index(x, p - 1);
    }
}
 
template<>
double index(double x, unsigned p) {
    std::cerr << "index<>(double, unsigned)\n";
    return pow(x, static_cast<double>(p));
}
 
int main() {
    auto a = index(-3, 4);
    std::cout << "(-3) ^ 4 = " << a << '\n';
    auto b = index(2.5, 2);
    std::cout << "2.5 ^ 2 = " << b << '\n';
}
