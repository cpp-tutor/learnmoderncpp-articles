#include <future>
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

const int sumSize = 1'000'000'000;

int main() {
    std::vector<int> summation(sumSize);
    std::iota(summation.begin(), summation.end(), 1);

    auto result1 = std::async([&]{ return std::accumulate(summation.begin(), summation.begin() + summation.size() / 4, 0LL); });
    auto result2 = std::async([&]{ return std::accumulate(summation.begin() + summation.size() / 4, summation.begin() + summation.size() / 2, 0LL); });
    auto result3 = std::async([&]{ return std::accumulate(summation.begin() + summation.size() / 2, summation.begin() + summation.size() * 3 / 4, 0LL); });
    auto result4 = std::async([&]{ return std::accumulate(summation.begin() + summation.size() * 3 / 4, summation.end(), 0LL); });
    auto sum = result1.get() + result2.get() + result3.get() + result4.get();

    std::cout << "Sum of first " << sumSize << " numbers is: " << sum << '\n';
}