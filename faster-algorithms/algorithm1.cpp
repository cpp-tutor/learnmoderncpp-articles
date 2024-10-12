#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ratio>
#include <chrono>
#include <cmath>
#include <numeric>
#include <algorithm>

template<typename T>
struct PythagoreanTriple {
    T a, b, c;
};
using Side = unsigned;

void get_triples(const Side limit_c, std::vector<PythagoreanTriple<Side>> &triples) {
    for (Side c = 5; c != limit_c; ++c) {
        for (Side b = 4; b != c; ++b) {
            for (Side a = 3; a != b; ++a) {
                if (a * a + b * b == c * c && std::gcd(std::gcd(a, b), c) == 1) {
                    triples.emplace_back(a, b, c);
                }
            }
        }
    }
}

int main(const int argc, const char **argv) {
    Side limit_c;
    if (argc == 2) {
        limit_c = std::atoi(argv[1]) + 1;
    }
    else {
        std::cout << "Maximum hypotenuse: ";
        std::string str;
        std::getline(std::cin, str);
        limit_c = std::atoi(str.c_str()) + 1;
    }
    std::vector<PythagoreanTriple<Side>> triples;
    auto time_point = std::chrono::high_resolution_clock::now();
    get_triples(limit_c, triples);
    auto time_elapsed = std::chrono::high_resolution_clock::now() - time_point;
    std::cout << "Time elapsed: " << std::setprecision(12) << std::chrono::duration<double,std::micro>(time_elapsed).count() << "us\n";
    std::cout << "Number of triples: " << triples.size() << "\nPress Enter to view...";
    std::string str;
    std::getline(std::cin, str);
    for (const auto& triple : triples) {
        std::cout << '(' << triple.a << ',' << triple.b << ',' << triple.c << ')' << ' ';
    }
}