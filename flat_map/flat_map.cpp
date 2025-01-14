// Tested with: https://raw.githubusercontent.com/tzlaine/flat_map/master/implementation/flat_map
#include <stdexcept>
#include "flat_map"
#include <string>
#include <string_view>
#include <iostream>
#include <cctype>

using namespace std;

class Person {
  string lastname, firstname;
  static string toUpper(string_view);
public:
  Person(string_view firstname, string_view lastname) : lastname{ lastname }, firstname{ firstname } {}
  friend bool operator<(const Person&, const Person&);
  friend ostream& operator<<(ostream&, const Person&);
};

bool operator<(const Person& lhs, const Person& rhs) {
    if (lhs.lastname != rhs.lastname) {
        return Person::toUpper(lhs.lastname) < Person::toUpper(rhs.lastname);
    }
    else {
        return Person::toUpper(lhs.firstname) < Person::toUpper(rhs.firstname);
    }
}

ostream& operator<<(ostream& os, const Person& p) {
    return os << p.firstname << ' ' << p.lastname;
}

string Person::toUpper(string_view s) {
    string upper;
    for (auto c : s) {
        if (isalpha(c)) {
            upper.push_back(toupper(c));
        }
    }
    return upper;
}

int main() {
    flat_map<Person,int> Scientists{
        { { "Albert", "Einstein" }, 1879 },
        { { "Marie", "Curie" }, 1867 },
        { { "Isaac", "Newton" }, 1643 },
        { { "Charles", "Darwin" }, 1809 },
        { { "Galileo", "Galilei" }, 1564 },
        { { "Nikola", "Tesla" }, 1856 },
        { { "Stephen", "Hawking" }, 1942 },
        { { "Alan", "Turing" }, 1912 }
    };
    for (const auto& s : Scientists) {
        cout << s.first << " born in " << s.second << '\n';
    }
}