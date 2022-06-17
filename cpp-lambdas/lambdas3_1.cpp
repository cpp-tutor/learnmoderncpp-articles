// lambdas3_1.cpp : lambda which outputs each element and calculates sum of all

#include <algorithm>
#include <iostream>
 
int main() {
    auto data = { 1.0, 2.2, 3.1, 2.1, 0.5, 1.6 };
    double sum{};
    auto sum_and_average = [&](const auto& elem){
        std::cout << elem << " ";
        sum += elem;
    };
    std::for_each(begin(data), end(data), sum_and_average);
    std::cout << "\nSum: " << sum << '\n';
}