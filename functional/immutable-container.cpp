#include <span>
#include <iostream>
#include <vector>
 
template<typename T>
void printContainer(const std::span<T> s, std::ostream& os = std::cout) {
    os << s.front();
    if (s.size() > 1) {
        os << ", ";
        printContainer(s.subspan(1), os);
    }
}
 
int main() {
    std::vector vi{ 1, 2, 3, 4, 5 };
    printContainer(std::span(vi));  // '1, 2, 3, 4, 5'
    std::cout << '\n';
    std::vector vf{ 1.1, 2.2, 3.3, 4.4 };
    printContainer(std::span(vf));  // '1.1, 2.2, 3.3, 4.4'
    std::cout << '\n';
}
