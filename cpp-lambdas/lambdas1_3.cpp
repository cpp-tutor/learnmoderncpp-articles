// lambdas1_3.cpp : accept and invoke simple lambda

#include <iostream>
#include <functional>
 
void f(std::function<void(void)> g) {
    g();
}
 
int main() {
    f([]{ std::cout << "Hello, lambdas!\n"; });
}