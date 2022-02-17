// json_any_1.cpp : build and output JSON object using std::any
// requires -std=c++17 or later

#include <any>
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;
using JSON = vector<pair<string,any>>;

ostream& operator<< (ostream& os, const JSON& json) {
    if (json.empty()) {
        return os << "{}";
    }
    auto sep = ""sv;
    os << "{ ";
    for (const auto& elem : json) {
        os << sep;
        if (elem.first.find(" ") != string::npos) {
            os << '\'' << elem.first << "\': ";
        }
        else {
            os << elem.first << ": ";
        }
        if (elem.second.type() == typeid(void)) {
            os << "undefined";
        }
        else if (elem.second.type() == typeid(double)) {
            os << any_cast<double>(elem.second);
        }
        else if (elem.second.type() == typeid(string)) {
            os << '\'' << any_cast<string>(elem.second) << '\'';
        }
        else if (elem.second.type() == typeid(JSON)) {
            os << any_cast<JSON>(elem.second);
        }
        sep = ", "sv;
    }
    return os << " }";
}

int main() {
    JSON obj;
    obj.emplace_back("a", JSON{});
    obj.emplace_back("b", any{});
    obj.emplace_back("c", 1.2);
    obj.emplace_back("d", "Hi!"s);
    cout << obj << '\n';
}
