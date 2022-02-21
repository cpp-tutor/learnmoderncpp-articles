// crtp_container.cpp : interface class with derived class using CRTP
// note: compile with -std=c++20 or later

#include <forward_list>
#include <iterator>
#include <initializer_list>
#include <iostream>

using namespace std;

template<typename Derived>
class Container {
    Derived& actual() {
        return *static_cast<Derived*>(this);
    }
    const Derived& actual() const {
        return *static_cast<const Derived*>(this);
    }
public:
    decltype(auto) front() {
        return *actual().begin();
    }
    decltype(auto) size() {
        return distance(actual().begin(), actual().end());
    }
    decltype(auto) operator[](size_t i) {
        return *next(actual().begin(), i);
    }
    void print(ostream& os = cout) {
        os << "{ ";
        for (auto sep = ""; const auto& elem : actual()) {
            os << sep << elem;
            sep = ", ";
        }
        os << " }\n";
    }
};

template<typename T>
class indexed_list : public Container<indexed_list<T>> {
    forward_list<T> l;
public:
    indexed_list(const initializer_list<T>& init_list) {
        l.assign(init_list);
    }
    decltype(auto) begin() {
        return l.begin();
    }
    decltype(auto) end() {
        return l.end();
    }
};

int main() {
    indexed_list il{ 1, 2, 3, 4, 5 };
    cout << "front(): " << il.front()
        << "\nsize(): " << il.size()
        << "\n[3]: " << il[3] << '\n';
    il[4] = 99;
    il.print();
}
