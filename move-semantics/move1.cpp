#include "Movable.hpp"

int main() {
    Movable m1{ "Apple "}, m2{ "Banana "}, m3{ "Clementine "}, m4{ "Date" };
    Movable m11{ m1 }, m12{ std::move(m2) }, m13, m14;
    m13 = m3;
    m14 = std::move(m4);
    m1.print();
    m2.print();
    m3.print();
    m4.print();
    m11.print();
    m12.print();
    m13.print();
    m14.print();
}