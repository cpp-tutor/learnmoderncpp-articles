// one_liner.cpp : store command line arguments in a C++ container
// requires -std=c++17 or later

#include <string_view>
#include <vector>
#include <iostream>

using std::string_view;
using std::vector;
using std::cout;

int main(const int argc, const char *argv[]) {
    vector<string_view> args{ argv, argv + argc };

    for (auto& arg : args) {
        cout << "-- " << arg << '\n';
    }
}
