#include <array>
#include <random>
#include <numeric>
#include <algorithm>
#include <iostream>
 
template<size_t N>
class RandomRange {
    std::array<int,N> range;
public:
    template<typename T>
    RandomRange(T& engine, int start = 0) {
        std::iota(range.begin(), range.end(), start);
        std::shuffle(range.begin(), range.end(), engine);
    }
    const std::array<int,N>& operator()() {
        return range;
    }
};
 
int main() {
    std::default_random_engine dre;
    RandomRange<9> r(dre, 1);
    for (const auto n : r()) {
        std::cout << "- " << n << '\n';
    }
}
