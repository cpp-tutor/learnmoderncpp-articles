#include "Movable.hpp"

void f(Movable&& obj) {
    std::cout << "Entering f()\n";
    obj.print();
    std::cout << "Leaving f()\n";
}

void g(Movable&& fwd) {
    std::cout << "Entering g()\n";
    f(std::forward<decltype(fwd)>(fwd));
    std::cout << "Leaving g()\n";
}

int main() {
    Movable m{ "Pass-by-forwarding-ref" };
    g(std::move(m));
    std::cout << "Leaving main()\n";
}