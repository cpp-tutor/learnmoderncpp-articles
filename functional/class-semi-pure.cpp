#include <iostream>
 
double random_lcg(unsigned seed = 0) {
    static unsigned int x = 1 << 19; // X(n+1) = (aX(n)+c) mod m
    if (seed) {
        x = seed;
        return 0.0;
    }
    x = (1103515245 * x + 12345) % (1u << 31);
    return x * 1.0 / (1u << 31);
}
 
class RandomLCG {
    unsigned int x;
public:
    RandomLCG(unsigned int seed = 1 << 19) : x{ seed } {}
    double operator()() {
        x = (1103515245 * x + 12345) % (1u << 31);
        return x * 1.0 / (1u << 31);
    }
};
 
int main() {
    random_lcg(42);
    std::cout << random_lcg() << ' ' << random_lcg() << ' ' << random_lcg() << '\n';
     
    RandomLCG random(42);
    std::cout << random() << ' ' << random() << ' ' << random() << '\n';
}
