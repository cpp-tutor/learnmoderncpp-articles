// container_types.cpp : print contents of any container with given value_type
// note: compile with -std=c++20 or later

#include <vector>
#include <list>
#include <iostream>

using namespace std;

template<typename T, template<typename = T, typename = allocator<T>> typename C>
void print(const C<T>& container) {
    cout << "{ ";
    for (auto separator = ""; const T& element : container) {
        cout << separator << element;
        separator = ", ";
    }
    cout << " }\n";
}

template<template<typename = int, typename = allocator<int>> typename C>
void print_int(const C<int>& container) {
    cout << "{ ";
    for (auto separator = ""; int element : container) {
        cout << separator << element;
        separator = ", ";
    }
    cout << " }\n";
}

int main() {
    vector vi{ 5, 4, 3, 2 ,1 };
    list ld{ 1.1, 2.2, 3.3, 4.4 };
    print(vi);
    print(ld);
    print_int(vi);
    // print_int(ld); // note: does not compile as ld contains doubles
}
