// new_namespace.cpp : populate a new namespace "ext" with elements of "std"
// requires -std=c++17 or later

#include <iostream>
#include <string_view>
#include <vector>

namespace ext {
    using std::cout;
    using std::ostream;
    using std::vector;
    using std::string_view;
}

using namespace std::string_view_literals;

namespace ext {
template <typename T>
ostream& operator<< (ostream& os, vector<T> vec) {
    if (vec.empty()) {
        return os << "{}"sv;
    }
    auto sep = ""sv;
    os << "{ "sv;
    for (const auto &elem : vec) {
        os << sep << elem;
        sep = ", "sv;
    }
    os << " }"sv;
    return os;
}
}

int main() {
    using namespace ext;
    vector<int> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    cout << primes << '\n';
    vector<string_view> odd{ "one"sv, "three"sv, "five"sv, "seven"sv, "nine"sv };
    cout << odd << '\n';
}
