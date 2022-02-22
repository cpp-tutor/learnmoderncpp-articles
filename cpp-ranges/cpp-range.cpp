// cpp-range.cpp : demonstration of range views and actions
// note: compile with -std=c++17 or later

#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <iostream>
#include <string_view>
#include <cctype>
#include <vector>

int main() {
    using namespace ranges;
    auto fruits = {
        "Apple", "pear", "banana", "MELON", "Pomegranate", "Orange", "asparagus"
    };

    auto selected_fruits = fruits
        | views::filter(
            [](std::string_view elem){
                return toupper(elem.front()) <= 'M';
            })
        | views::transform(
            [](std::string_view elem){
                std::string s{};
                for (auto c : elem) {
                    s += toupper(c);
                }
                return s;
            })
        | to<std::vector>()
        | actions::sort
        ;

    for (const auto& f : selected_fruits) {
        std::cout << f << '\n';
    }
}
