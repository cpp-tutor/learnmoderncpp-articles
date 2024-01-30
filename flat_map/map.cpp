#include <map>
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
    map<Person,int> Presidents{
        { { "George HW", "Bush" }, 1988 },
        { { "Bill", "Clinton" }, 1992 },
        { { "George W", "Bush" }, 2000 },
        { { "Barack", "Obama" }, 2008 },
        { { "Donald", "Trump" }, 2016 },
        { { "Joe", "Biden" }, 2020 }
    };
    for (const auto& p : Presidents) {
        cout << p.first << " elected in " << p.second << '\n';
    }
}
