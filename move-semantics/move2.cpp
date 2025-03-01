#include "Movable.hpp"

void f(Movable obj) {
    std::cout << "Entering f()\n";
    obj.print();
    std::cout << "Leaving f()\n";
}

int main() {
    Movable m{ "Pass-by-value" };
    f(std::move(m));
    std::cout << "Leaving main()\n";
}
