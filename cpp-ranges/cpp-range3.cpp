// cpp-range3.cpp : sum of the first million primes
// note: compile with -std=c++17 or /std:c++20

#include <range/v3/view.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <iostream>
#include <vector>

using namespace ranges::v3;

int main() {
    std::vector<unsigned long long> primes{};
    auto is_prime = [&primes](auto n){
        for (auto p : primes) {
            if (n % p == 0) {
                return false;
            }
            if (p * p > n) {
                break;
            }
        }
        primes.push_back(n);
        return true;
    };

    auto pipeline = views::iota(2)
        | views::filter(is_prime)
        | views::take(1'000'000);
    std::cout << "Sum of the first million primes is: " << accumulate(pipeline, unsigned long long{}) << '\n';
}
