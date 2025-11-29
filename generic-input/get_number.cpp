#include <charconv>
#include <string>
#include <string_view>
#include <print>
#include <iostream>
#include <exception>

class FromCharsException : public std::exception {
    std::errc ec;
public:
    FromCharsException() = delete;
    FromCharsException(std::errc error_code)
        : ec{ error_code } {}
    const char* what() const noexcept override final {
        return "from_chars() exception";
    }
    auto get() const noexcept { return ec; }
};

template<typename T>
std::pair<T,const char*> get_from_chars(std::string_view s) {
    using std::from_chars;
    T value;
    auto rc = from_chars(s.data(), s.data() + s.size(), value);
    if (rc.ec != std::errc{}) {
        throw FromCharsException(rc.ec);
    }
    return std::pair{ value, rc.ptr };
}

template<typename T>
T get(std::istream& is = std::cin) {
    std::string str;
    is >> str;
    return get_from_chars<T>(str).first;
}

template<typename... Ts>
std::istream& getline(std::istream& is, Ts&... values) {
    using std::getline;
    std::string str;
    getline(is, str);
    std::string_view sv{ str };
    auto get_number = [&sv](auto& value){
        std::string_view ws{ " \t\f" };
        while (ws.find(sv.front()) != std::string::npos) {
            sv.remove_prefix(1);
        }
        auto result = get_from_chars<std::remove_reference_t<decltype(value)>>(sv);
        value = result.first;
        sv.remove_prefix(result.second - sv.data());
    };
    ((get_number(values)), ...);
    return is;
}

int main() {
    std::println("Enter an integer, a float and another integer:");
    int a, c;
    float b;
    getline(std::cin, a, b, c);
    std::println("{} {} {}", a, b, c);
}
