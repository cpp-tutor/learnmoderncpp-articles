#include "printf_to_string.hpp"
#include <iostream>

int main() {
    auto s1 = string_printf("Hello, world!\n");
    auto s2 = string_printf("Hello, %s%c\n", "world", '!');
    if (s1 == s2) {
        std::cout << "Strings are the same.\n";
    }
    else {
        std::cout << "Strings are not the same.\n";
    }
}