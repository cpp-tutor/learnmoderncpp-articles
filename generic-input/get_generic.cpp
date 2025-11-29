#include <print>
#include <string>
#include <sstream>
#include <istream>
#include <iostream>

template<typename T>
T get(std::istream& is = std::cin) {
    T input;
    is >> input;
    return input;
}

template<typename... Ts>
std::istream& get(std::istream& is, Ts&... inputs) {
    ((is >> inputs), ...);
    return is;
}

template<typename... Ts>
auto getline(std::istream& is, Ts&... inputs) {
    using std::getline;
    std::string inputline;
    getline(is, inputline);
    std::istringstream iss{ inputline };
    ((iss >> inputs), ...);
    return iss.rdstate();
}

int main() {
    std::println("Enter number op number (eg. 1.2 + 3.4):");
    double a, b;
    char op;
    auto st = getline(std::cin, a, op, b);
    std::println("{} {} {}", a, op, b);
}
