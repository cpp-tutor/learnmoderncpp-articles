// this-class.cpp : deducing this for class and auto-generating const/non-const member at()
// Note: compile with VS2022 C++ /std:c++latest

#include <iostream>
#include <array>
 
template<typename T, size_t X, size_t Y>
struct Matrix {
    std::array<T, X * Y> data{};
 
    template<typename Self>
    auto& at(this Self&& self, size_t x, size_t y) {
        return std::forward<Self>(self).data.at(y * X + x);
    }
};
 
int main() {
    Matrix<int, 2, 3> mat{};
    mat.at(1, 1) = -9;
    std::cout << mat.at(1, 1) << '\n';
}
