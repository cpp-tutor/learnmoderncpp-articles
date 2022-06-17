// lambdas1_1.cpp : define and invoke simple lambda

#include <iostream>
 
void f() {
    auto g = []{
        std::cout << "Hello, lambdas!\n";
    };
    g();
}
 
int main() {
    f();
}
