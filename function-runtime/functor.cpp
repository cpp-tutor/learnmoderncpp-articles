#include <iostream>
#include <cmath>

class DivideToInt {
    double divisor, dividend;
public:
    enum class Policy { Ceiling, Floor, Nearest };
    DivideToInt(double divisor, double dividend)
        : divisor{ divisor }, dividend{ dividend } {}
    int operator()(Policy policy) {
        double(*df)(double);
        switch (policy) {
            case Policy::Ceiling:
                df = &ceil;
                break;
            case Policy::Floor:
                df = &floor;
                break;
            case Policy::Nearest:
                df = &round;
                break;
        }
        return (*df)(divisor / dividend);
    }
};

int main() {
    DivideToInt division(7.0, 3.3);
    std::cout << "ceil(7.0 / 3.3) = " << division(DivideToInt::Policy::Ceiling) << '\n';
    std::cout << "floor(7.0 / 3.3) = " << division(DivideToInt::Policy::Floor) << '\n';
    std::cout << "round(7.0 / 3.3) = " << division(DivideToInt::Policy::Nearest) << '\n';
}
