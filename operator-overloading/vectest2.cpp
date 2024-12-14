#include "Vec3d.hpp"
#include <iostream>

int main() {
    Vec3d v(2.0, 4.0, 3.0), w(1.0, 5.0, -2.0), z = v + w;
    std::cout << z << '\n';
    std::cout << 3.0 * v << ' ' << w / 2.0 << '\n';
}