#include <iostream>
 
class B3 {
public:
    virtual void f() = 0;
    virtual void g() { std::cout << "B3::g()\n"; }
};
 
class D3 : public B3 {
public:
    virtual void f() override { std::cout << "D3::f()\n"; }
};
 
class E3 : public D3 {
public:
    virtual void f() override { std::cout << "E3::f()\n"; }
    virtual void h() { std::cout << "E3::h()\n"; }
};
 
class F3 : public B3 {
public:
    virtual void f() { B3::f(); }
};
     
void B3::f() {  // definition of a pure virtual function
    std::cout << "B3::f()\n";
}
 
int main() {
    D3 a;
    a.f();
    a.g();
    E3 b;
    b.f();
    b.g();
    b.h();
    F3 c;
    c.f();
}
