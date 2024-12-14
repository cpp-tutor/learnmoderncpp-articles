#include "Vec3d.hpp"
#include <iostream>

int main() { 
   double d = 2.2;
    Vec3d v(1.1, d, 3.3), w;
    w += -v;
    std::cout << v << '\n' << w.dot(v) << '\n';
    Vec3d x(2.0, 4.0, 3.0), y(1.0, 5.0, -2.0), z;
    z = x.cross(y);
    std::cout << z << '\n';
}