// print_tuple1.cpp : output a tuple using class and member function templates with TMP
// note: compile with -std=c++17 or later

#include <iostream>
#include <tuple>

using namespace std;

template<size_t N>
struct TupleOstream {
    template<typename... Args>
    static void print(ostream& os, const tuple<Args...>&t) {
        os << get<sizeof...(Args) - N - 1>(t) << ", ";
        TupleOstream<N - 1>::print(os, t);
    }
};

template<>
struct TupleOstream<0> {
    template<typename... Args>
        static void print(ostream& os, const tuple<Args...>&t) {
        os << get<sizeof...(Args) - 1>(t);
    }
};

template<typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    if constexpr (sizeof...(Args) == 0) {
        return os << "{}";
    }
    else {
        os << "{ ";
        TupleOstream<sizeof...(Args) - 1>::print(os, t);
        return os << " }";
    }
}

int main() {
    tuple my_tuple{ "Hi", 2, 0xALL, 0U, "folks!" };
    cout << my_tuple << '\n';
}
