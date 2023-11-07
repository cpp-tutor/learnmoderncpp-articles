#include <expected>
#include <iostream>
#include <variant>
#include <initializer_list>

class OverflowFromDoubling {};
class OverflowFromAddingThree {};

using Error = std::variant<OverflowFromDoubling,OverflowFromAddingThree>;
using ResultOrError = std::expected<int,Error>;

int main() {
    const int overflow = 10;
    auto doubleMe = [&overflow](int n) -> ResultOrError {
        n = n * 2;
        if (n < overflow) {
            return n;
        }
        else {
            return std::unexpected{ OverflowFromDoubling{} };
        }
    };
    auto addThree = [&overflow](int n) -> ResultOrError {
        n = n + 3;
        if (n < overflow) {
            return n;
        }
        else {
            return std::unexpected{ OverflowFromAddingThree{} };
        }
    };
    for (auto number : { 1, 2, 3, 4, 5 }) {
        auto result = doubleMe(number).and_then(addThree);
        std::cout << number << ": ";
        if (result.has_value()) {
            std::cout << result.value() << '\n';
        }
        else {
            switch (result.error().index()) {
                case 0:
                    std::cout << "Overflow from doubling\n";
                    break;
                case 1:
                    std::cout << "Overflow from adding three\n";
                    break;
                default:
                    break;
            }
        }
    }
}
