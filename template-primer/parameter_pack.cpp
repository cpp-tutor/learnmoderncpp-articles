// parameter_pack.cpp : demonstrate forwarding of variadic parameter packs

#include <iostream>

using namespace std;

template<typename T> // note: base case must be declared or defined before general case
void print(const T& head) {
    cout << head;
}

template<typename T, typename... Ts>
void print(const T& head, const Ts... tail) {
    cout << head << ' ';
    print(tail...); // note: recursive function call
}

int main() {
    print(1.0, "man", "went", 2, "mow", '\n');
}
