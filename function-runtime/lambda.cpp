#include <functional>
#include <iostream>
#include <cmath>
#include <initializer_list>

enum class DivisionPolicy { Ceiling, Floor, Nearest };

int main() {
    std::function<int(double,double)> df;
    for (auto p : { DivisionPolicy::Ceiling, DivisionPolicy::Floor, DivisionPolicy::Nearest }) {
        switch (p) {
            case DivisionPolicy::Ceiling:
                df = [](double a, double b) -> int { return ceil(a / b); };
                break;
            case DivisionPolicy::Floor:
                df = [](double a, double b) -> int { return floor(a / b); };
                break;
            case DivisionPolicy::Nearest:
                df = [](double a, double b) -> int { return round(a / b); };
                break;
        }
        std::cout << static_cast<int>(p) << ": " << df(7.0, 3.3) << '\n';
    }
}
