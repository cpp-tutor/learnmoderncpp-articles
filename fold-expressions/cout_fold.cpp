// cout_fold.cpp : use of output stream with folding expression
// note: compile with -std=c++17 or later

#include <iostream>

using namespace std;

template<typename... Ts>
void print_all(Ts&&... args) {
    (cout << ... << args);
}

int main() {
    print_all(42, "hello", 1.23, '\n');
}
