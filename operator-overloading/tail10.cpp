#include "CircularArray.hpp"
#include <string>
#include <iostream>

int main() {
    CircularArray<std::string,10> buffer;
    std::string str;
    getline(std::cin, str);
    while (!std::cin.eof() && !str.empty()) {
        buffer = str;
        getline(std::cin, str);
    }
    while (!buffer.hasData()) {
        ++buffer;
    }
    for (int i = 0; i != 10; ++i) {
        if (buffer.hasData()) {
            std::cout << *buffer << '\n';
            ++buffer;
        }
    }
}