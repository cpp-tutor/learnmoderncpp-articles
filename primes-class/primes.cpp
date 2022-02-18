// primes.cpp : efficiently verify whether a number is prime
// Version 1.00 2020/12/24, (c) Richard Spencer 2020, MIT License

#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T = unsigned>
class Primes {
    vector<T> primes_cache{ 2, 3 };
    typename vector<T>::size_type cache_step;
    void generate(typename vector<T>::size_type step) {
        auto new_size = primes_cache.size() + step;
        auto p = primes_cache.back();
        while (primes_cache.size() < new_size) {
            if (isPrime(++p, false)) {
                primes_cache.push_back(p);
            }
        }
    }
public:
    Primes(typename vector<T>::size_type step = 1000)
        : cache_step{step} {
        generate((step > 2) ? step - 2 : step);
    }
    template <typename U>
    bool isPrime(const U& n, bool gen = true) {
        while (gen && ((primes_cache.back() * primes_cache.back()) <= n)) {
            generate(cache_step);
        }
        for (const auto& p : primes_cache) {
            if (!(n % p)) {
                return false;
            }
            if ((p * p) >= n) {
                return true;
            }
        }
        throw runtime_error("Insufficient primes in cache");
    }
};

int main() {
    Primes<unsigned long long> primes{};
    for (unsigned i = 2; i < 200; ++i) {
        if (primes.isPrime(i)) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}
