// lambdas4_2.cpp : lambdas4_1 rewritten as a functor

#include <iostream>
 
struct S {
    int a;
    void operator()() const {
        std::cout << "S(): a = " << a << '\n';
    }
};
 
auto f() {
    int a{ 1 };
    S l{ a };
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