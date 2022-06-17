// lambdas1_2.cpp : define and return simple lambda

#include <iostream>
 
auto f() {
    auto g = []{
        std::cout << "Hello, lambdas!\n";
    };
    return g;
}
 
int main() {
    f()();
}