// fold_seq.cpp : use folding expressions to calculate sum and product of a number sequence
// note: compile with -std=c++17 or later

#include <iostream>
#include <utility>

using namespace std;

template<size_t Zero, size_t... Numbers>
void sum_product(index_sequence<Zero, Numbers...> seq)
{
    cout << "Numbers: ";
    ((cout << Numbers << ' '), ...);
    cout << '\n';
    
    auto s1 = (Numbers + ...);      // unary right fold
    auto p1 = (... * Numbers);      // unary left fold
    auto s2 = (Numbers + ... + 0);  // binary right fold
    auto p2 = (1 * ... * Numbers);  // binary left fold
    
    auto s3{ 0 }, p3{ 1 };
    (s3 += ... += Numbers);         // binary left folds using
    (p3 *= ... *= Numbers);         // right-associative operators
    
    cout << "Sum: " << s1 << ", " << s2 << ", " << s3 << '\n';
    cout << "Product: " << p1 << ", " << p2 << ", " << p3 << '\n';
}

int main() {
    using numbers = make_index_sequence<6>; // 0..5
    sum_product(numbers{});
}
