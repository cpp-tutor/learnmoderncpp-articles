// lambdas1_4.cpp : accept and call lambda with parameter

#include <iostream>
#include <functional>
 
void f(std::function<int(int)> g, int i) {
    std::cout << "f(): " << g(i) << '\n';
}
 
int main() {
    auto increment = [](int a){ return a + 1; };
    auto decrement = [](int a){ return a - 1; };
 
    f(increment, 10);
    f(decrement, 0);
}