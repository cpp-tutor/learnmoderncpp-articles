#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <mutex>
#include <ratio>
#include <chrono>
#include <numeric>
#include <cmath>
#include <execution>
#include <algorithm>

template<typename T>
struct PythagoreanTriple {
    T a, b, c;
};
using Side = unsigned;

template<typename T>
void get_triples(const T policy, const Side limit_c, std::vector<PythagoreanTriple<Side>> &triples) {
    std::mutex mut;
    std::vector<Side> side_c(limit_c - 1);
    std::iota(side_c.begin(), side_c.end(), 1);
    std::for_each(policy, side_c.cbegin(), side_c.cend(), [&triples,&mut](const Side c){
        for (Side b = 1; b != c; ++b) {
            Side limit_a = sqrt(c * c - b * b) + 1;
            for (Side a = c - b; a < limit_a && a < b; ++a) {
                if (a * a + b * b == c * c && std::gcd(std::gcd(a, b), c) == 1) {
                    std::unique_lock<std::mutex> lock(mut);
                    triples.emplace_back(a, b, c);
                    break;
                }
            }
        }
    });
}

int main(const int argc, const char **argv) {
    Side limit_c;
    if (argc >= 2) {
        limit_c = std::atoi(argv[1]) + 1;
    }
    else {
        std::cout << "Maximum hypotenuse: ";
        std::string str;
        std::getline(std::cin, str);
        limit_c = std::atoi(str.c_str()) + 1;
    }
    int policy;
    if (argc == 3) {
        policy = std::atoi(argv[2]);
    }
    else {
        std::cout << "Execution policy: 1) seq, 2) unseq, 3) par, 4) par_unseq: ";
        std::string str;
        std::getline(std::cin, str);
        policy = std::atoi(str.c_str());
    }
    std::vector<PythagoreanTriple<Side>> triples;
    auto time_point = std::chrono::high_resolution_clock::now();
    switch (policy) {
        case 2:
            get_triples(std::execution::unseq, limit_c, triples);
            break;
        case 3:
            get_triples(std::execution::par, limit_c, triples);
            break;
        case 4:
            get_triples(std::execution::par_unseq, limit_c, triples);
            break;
        default:
            get_triples(std::execution::seq, limit_c, triples);
            break;
    }
    auto time_elapsed = std::chrono::high_resolution_clock::now() - time_point;
    std::cout << "Time elapsed: " << std::setprecision(12) << std::chrono::duration<double,std::micro>(time_elapsed).count() << "us\n";
    std::cout << "Number of triples: " << triples.size() << "\nPress Enter to view...";
    std::cin.get();
    if (!std::cin.eof()) {
        std::sort(triples.begin(), triples.end(), [](const PythagoreanTriple<Side>& p, const PythagoreanTriple<Side>& q){
            return (p.c == q.c) ? p.b < q.b : p.c < q.c;
        });
        for (const auto& triple : triples) {
            std::cout << '(' << triple.a << ',' << triple.b << ',' << triple.c << ')' << ' ';
        }
    }
}