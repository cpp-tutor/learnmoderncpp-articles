// sfinae_tostring.cpp : use of SFINAE with traits and enable_if 
// note: compile with -std=c++20 or later

#include <type_traits>
#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

using namespace std;

class Book {
    string d_title;
    vector<string> d_authors;
public:
    Book(const string& title, const initializer_list<string>& authors)
        : d_title{ title }, d_authors{ authors }
    {}
    string to_string() const {
        string s{}, sep{};
        for (const auto& a : d_authors) {
            s.append(sep);
            s.append(a);
            sep = ", "s;
        }
        s.append(": ");
        s.append(d_title);
        return s;
    }
};

template<typename, typename = std::void_t<>>
struct HasMemberT_toString : false_type{};

template<typename T>
struct HasMemberT_toString<T, void_t<decltype(declval<T>().to_string())>> : true_type{};

static_assert(HasMemberT_toString<Book>::value);

template<typename T>
enable_if<HasMemberT_toString<T>::value, ostream&>::type
operator<< (ostream& os, const T& obj) {
    return os << obj.to_string();
}

int main() {
    Book book1{ "C++ Annotations", { "Frank B. Brokken" } },
        book2{ "C++ Templates", { "David Vandevoorde", "Nicolai M. Josuttis", "Douglas Gregor" } };
    cout << book1 << '\n' << book2 << '\n';
}
