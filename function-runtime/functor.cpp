#include <iostream>
#include <cmath>

class DivideCeiling {};
class DivideFloor {};
class DivideNearest {};

class DivideToInt {
    double divisor, dividend;
public:
    DivideToInt(double divisor, double dividend)
        : divisor{ divisor }, dividend{ dividend } {}
    int operator()(const DivideCeiling&) {
        return ceil(divisor / dividend);
    }
    int operator()(const DivideFloor&) {
        return floor(divisor / dividend);
    }
    int operator()(const DivideNearest&) {
        return round(divisor / dividend);
    }
};

int main() {
    DivideToInt division(7.0, 3.3);
    std::cout << "ceil(7.0 / 3.3) = " << division(DivideCeiling{}) << '\n';
    std::cout << "floor(7.0 / 3.3) = " << division(DivideFloor{}) << '\n';
    std::cout << "round(7.0 / 3.3) = " << division(DivideNearest{}) << '\n';
}
