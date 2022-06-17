// lambdas3_3.cpp : functor with same functionality as lambdas3_1.cpp

#include <algorithm>
#include <iostream>
 
struct Sum {
    double sum{};
    template<typename T>
    void operator() (const T& elem) {
        std::cout << elem << " ";
        sum += elem;
    }
};

int main() {
    auto data = { 1.0, 2.2, 3.1, 2.1, 0.5, 1.6 };
    Sum s;
    std::for_each(begin(data), end(data), std::ref(s));
    std::cout << "\nSum: " << s.sum << '\n';
}