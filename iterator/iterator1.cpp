// iterator1.cpp : traverse an array backwards using const-reverse iterator

#include <iostream>
 
int main() {
    const int arr[] = { 1, 2, 3, 4, 5, 6 };
    for (auto elem = std::crbegin(arr); elem != std::crend(arr); ++elem) {
        std::cout << *elem << ' ';
    }
    std::cout << '\n';
}
