// non-range.cpp : cumulative operations on containers using standard algorithms
// note: compile with -std=c++17 or later

#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <cctype>
#include <iostream>

int main() {
    auto fruits = { "Apple", "pear", "banana", "MELON", "Pomegranate", "Orange", "asparagus" };

    std::vector<std::string> selected_fruits{};
    std::copy_if(std::begin(fruits), std::end(fruits), std::back_inserter(selected_fruits),
        [](std::string_view elem){ return toupper(elem.front()) <= 'M'; }
    );
    std::for_each(std::begin(selected_fruits), std::end(selected_fruits),
        [](std::string& s){
            for (auto &c : s) {
                c = toupper(c);
            }
        }
    );
    std::sort(std::begin(selected_fruits), std::end(selected_fruits));

    for (const auto& f : selected_fruits) {
        std::cout << f << '\n';
    }
}
