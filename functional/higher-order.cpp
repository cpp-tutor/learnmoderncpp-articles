#include <iostream>
#include <vector>
#include <algorithm>
 
int main() {
    std::vector v{ 0, 1, 2, 3, 4, 5 };
 
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';  // '0 1 2 3 4 5 '
     
    std::for_each(v.begin(), v.end(), [&v](const auto& value){
        std::cout << value;
        std::cout << ((&value == &v.back()) ? "\n" : ", ");
    });  // '0, 1, 2, 3, 4, 5'
}
