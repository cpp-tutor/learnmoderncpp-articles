// lambdas4_3.cpp : mutable lambda which captures by copy

#include <iostream>
 
auto f() {
    int a{ 1 };
    auto l = [=]() mutable { std::cout << "l(): a = " << a-- << '\n'; };
    a = 2;
    l();
    a = 3;
    l();
    a = 4;
    return l;
}
 
int main() {
    f()();
}