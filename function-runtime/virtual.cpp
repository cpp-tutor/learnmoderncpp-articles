#include <iostream>
#include <cmath>

class DivideToInt {
protected:
    double divisor, dividend;
public:
    DivideToInt(double divisor, double dividend) : divisor{ divisor }, dividend{ dividend } {}
    virtual int div() const = 0;
};

class CeilingDivide : public DivideToInt {
public:
    using DivideToInt::DivideToInt;
    virtual int div() const override {
        return static_cast<int>(ceil(divisor / dividend));
    }
};

class FloorDivide : public DivideToInt {
public:
    using DivideToInt::DivideToInt;
    virtual int div() const override {
        return static_cast<int>(floor(divisor / dividend));
    }
};

class NearestDivide : public DivideToInt {
public:
    using DivideToInt::DivideToInt;
    virtual int div() const override {
        return static_cast<int>(round(divisor / dividend));
    }
};

int main() {
    DivideToInt *divisions[3];
    divisions[0] = new CeilingDivide(7.0, 3.3);
    divisions[1] = new FloorDivide(7.0, 3.3);
    divisions[2] = new NearestDivide(7.0, 3.3);
    std::cout << "ceil(7.0 / 3.3) = " << divisions[0]->div() << '\n';
    std::cout << "floor(7.0 / 3.3) = " << divisions[1]->div() << '\n';
    std::cout << "round(7.0 / 3.3) = " << divisions[2]->div() << '\n';
}
