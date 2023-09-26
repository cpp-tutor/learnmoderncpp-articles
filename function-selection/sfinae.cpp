#include <iostream>
#include <cmath>
#include <utility> // for std::declval<T>
#include <type_traits> // for std::enable_if
 
template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, T>
index(T x, unsigned p) {
    if (p == 0) {
        std::cerr << "index<T>()\n";
        return 1;
    }
    else {
        return x * index(x, p - 1);
    }
}
 
template<typename T>
typename std::enable_if_t<!std::is_integral_v<T>
    && !std::is_void_v<decltype(std::pow(std::declval<T>(), 0u))>, T>
index(T x, unsigned p) {
    std::cerr << "index(pow)\n";
    return pow(x, p);
}
 
int main() {
    auto a = index(-3, 4);
    std::cout << "(-3) ^ 4 = " << a << '\n';
    auto b = index(2.5, 2);
    std::cout << "2.5 ^ 2 = " << b << '\n';
}
