// cpp-range3.cpp : sum of the first million primes
// note: compile with -std=c++23 or /std:c++latest

#include <ranges>
#include <numeric>
#include <vector>
#include <iostream>
 
using namespace std::ranges;
 
int main() {
    auto is_prime = [](auto n){
        if (n < 2) {
            return false;
        }
        else if (n < 4) {
            return true;
        }
        else if (n % 2 == 0) {
            return false;
        }
        else for (int p = 3; p != n; p += 2) {
            if (n % p == 0) {
                return false;
            }
            if (p * p > n) {
                break;
            }
        }
        return true;
    };
 
    auto pipeline = views::iota(2)
        | views::filter(is_prime)
        | views::take(1'000'000)
        | to<std::vector>();
    std::cout << "Sum of the first million primes is: " << std::accumulate(pipeline.begin(), pipeline.end(), 0ULL) << '\n';
}