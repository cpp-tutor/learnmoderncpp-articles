// print_tuple2.cpp : output a tuple using recursive call and constexpr condition test
// note: compile with -std=c++17 or later

#include <iostream>
#include <tuple>

using namespace std;

template<size_t N, typename... Args>
void print(ostream& os, const tuple<Args...>&t) {
    os << get<sizeof...(Args) - N - 1>(t);
    if constexpr (N > 0) {
        os << ", ";
        print<N - 1, Args...>(os, t);
    }
}

template<typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    if constexpr (sizeof...(Args) == 0) {
        return os << "{}";
    }
    else {
        os << "{ ";
        print<sizeof...(Args) - 1,Args...>(os, t);
        return os << " }";
    }
}

int main() {
    tuple my_tuple{ "Hi", 2, 0xALL, 0U, "folks!" };
    cout << my_tuple << '\n';
}
