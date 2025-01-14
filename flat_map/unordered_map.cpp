#include <unordered_map>
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
  friend bool operator==(const Person&, const Person&);
  friend ostream& operator<<(ostream&, const Person&);
  friend class hash<Person>;
};

bool operator==(const Person& lhs, const Person& rhs) {
    return Person::toUpper(lhs.lastname + ',' + lhs.firstname)
        == Person::toUpper(rhs.lastname + ',' + rhs.firstname);
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

namespace std {
template <>
struct hash<Person> {
    size_t operator()(const Person& p) const {
        return hash<string>()(p.firstname + p.lastname);
    }
};
}

int main() {
    unordered_map<Person,int> Scientists{
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