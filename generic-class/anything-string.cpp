#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
 
using namespace std::literals;
 
class AnythingString {
    std::string str;
public:
    AnythingString() {}
    AnythingString(std::string_view value) {
        str = value;
        std::cerr << "string_view specialization called\n";
    }
    template<typename T>
    AnythingString(const T& value) {
        std::ostringstream oss;
        oss << value;
        str = oss.str();
        std::cerr << "generic conversion called\n";
    }
    template<typename T>
    AnythingString& operator=(const T& value) {
        str = AnythingString(value).get();
        return *this;
    }
    template<typename T>
    AnythingString& operator+=(const T& value) {
        str += AnythingString(value).get();
        return *this;
    }
    std::string_view get() const { return str; }
};
 
std::ostream& operator<<(std::ostream& os, const AnythingString& s) {
    return os << s.get();
}
 
int main() {
    AnythingString s = 1.23;
    s += ' ';
    s += 45;
    s += " anything"sv;
    std::cout << s << '\n';
}
