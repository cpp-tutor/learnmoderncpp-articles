#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <initializer_list>

std::unordered_map<std::string, std::function<int(double,double)>> DivisionPolicy = {
    { "ceiling", [](double a, double b) -> int { return ceil(a / b); } },
    { "floor", [](double a, double b) -> int { return floor(a / b); } },
    { "nearest", [](double a, double b) -> int { return round(a / b); } }
};

int main() {
    for (auto p : { "ceiling", "floor", "nearest" }) {
        std::cout << p << ": " << DivisionPolicy[p](7.0, 3.3) << '\n';
    }
}
