// lambdas3_2.cpp : lambda which calculates a running sum and mean average of all elements

#include <algorithm>
#include <iostream>
 
int main() {
    auto data = { 1.0, 2.2, 3.1, 2.1, 0.5, 1.6 };
    double sum{}, average{};
    unsigned count{};
    auto sum_and_average = [&](const auto& elem){
        std::cout << elem << " ";
        ++count;
        sum += elem;
        average = sum / count;
    };
    std::for_each(begin(data), begin(data) + size(data) / 2, sum_and_average);
    std::cout << "\nSum (1/2): " << sum << ", Average (1/2): " << average << '\n';
    std::for_each(begin(data) + size(data) / 2, end(data), sum_and_average);
    std::cout << "\nSum: " << sum << ", Average: " << average << '\n';
}