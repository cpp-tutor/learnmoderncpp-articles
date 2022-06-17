// lambdas3_4.cpp : functor from lambdas3_3.cpp with reference member variable

#include <algorithm>
#include <iostream>
 
struct Sum {
    double& d_sum;
    Sum(double &s) : d_sum{ s } {}
    template<typename T>
    void operator() (const T& elem) {
        std::cout << elem << " ";
        d_sum += elem;
    }
};

int main() {
    auto data = { 1.0, 2.2, 3.1, 2.1, 0.5, 1.6 };
    double sum{};
    Sum s(sum);
    std::for_each(begin(data), end(data), s);
    std::cout << "\nSum: " << sum << '\n';
}