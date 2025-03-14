#include "Movable.hpp"

void f(Movable&& ref) {
    Movable obj = std::move(ref);
    std::cout << "Entering f()\n";
    obj.print();
    std::cout << "Leaving f()\n";
}

int main() {
    Movable m{ "Pass-by-universal-ref" };
    f(std::move(m));
    std::cout << "Leaving main()\n";
}