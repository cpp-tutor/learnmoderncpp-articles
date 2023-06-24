#include <iostream>
#include <string>
#include <string_view>
 
template<typename T>
class Named {
    T value;
    std::string name;
public:
    Named(const T& value, std::string_view name)
        : value{value}, name{name} {}
    const T& get() const { return value; }
    std::string_view get_name() const { return name; }
};
 
template<typename T>
std::ostream& operator<<(std::ostream& os, const Named<T>& n) {
    return os << n.get_name() << ':' << n.get();
}
 
int main() {
    Named i(42, "answer");
    Named p(3.14, "pi");
    std::cout << i << '\n' << p << '\n';
}
