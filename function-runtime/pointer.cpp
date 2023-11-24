#include <iostream>

int floor_divide(double a, double b) {
    return static_cast<int>(a / b);
}

int main() {
    int(*pf1)(double, double) = &floor_divide;  // C-style function pointer

    using PFType = int(*)(double, double);     // Modern C++ using-declaration
    PFType pf2 = &floor_divide;
    
    std::cout << "floor(7.0 / 3.3) = " << (*pf1)(7.0, 3.3) << '\n';
    std::cout << "floor(7.0 / 3.3) = " << (*pf2)(7.0, 3.3) << '\n';
}
