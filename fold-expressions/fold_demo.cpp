// fold_demo.cpp : get and print three variables of different types
// note: compile with -std=c++17 or later

#include <iostream>
#include <string>

using namespace std;

template<typename T, typename... Ts>
ostream& print_all(ostream& out, T&& arg0, Ts&&... args) {
    out << forward<T>(arg0);
    if (sizeof...(args) > 0) {
        ((out << ", " << forward<Ts>(args)), ...);
    }
    return out;
}

template<typename... Ts>
istream& input_all(istream& in, Ts&... args) {
    return (in >> ... >> args);
}

int main() {
    cout << "Please enter an integer, a single word and a floating-point number, separated by a space:\n";
    int i; string s; double d;
    input_all(cin, i, s, d);
    cout << "You entered: \"";
    print_all(cout, i, s, d);
    cout << "\"\n";
}
