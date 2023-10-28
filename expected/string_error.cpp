#include <expected>
#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>
 
enum class Error { None, TooBig, TooSmall, Answer };
using StringOrError = std::expected<std::string,Error>;
 
auto toString(int n) -> StringOrError {
    if (0 > n) {
        return std::unexpected{ Error::TooSmall };
    }
    else if (100 <= n) {
        return std::unexpected{ Error::TooBig };
    }
    else if (42 == n) {
        return std::unexpected{ Error::Answer };
    }
    else {
        auto s = std::to_string(n);
        return s;
    }
}

int main() {
    try {
        for (auto number : { 1, 99, -1, 100, 42, 99 }) {
            auto result = toString(number);
            if (result.has_value()) {
                std::cout << "Value: " << result.value() << '\n';
            }
            else {
                if (result.error() == Error::Answer) {
                    throw std::runtime_error("Found the answer");
                }
                std::cerr << "Error: " << static_cast<int>(result.error()) << '\n';
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }
}
