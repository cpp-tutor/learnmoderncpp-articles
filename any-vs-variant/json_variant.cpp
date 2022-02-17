// json_variant.cpp : build and output JSON object using std::variant
// requires -std=c++17 or later

#include <variant>
#include <vector>
#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <iostream>

using namespace std;

struct JSON_s;
using JSON = vector<pair<string,variant<monostate,double,string,unique_ptr<JSON_s>>>>;
struct JSON_s {
    JSON data;
};

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
        switch (elem.second.index()) {
            case 0:
                os << "undefined";
                break;
            case 1:
                os << get<double>(elem.second);
                break;
            case 2:
                os << '\'' << get<string>(elem.second) << '\'';
                break;
            case 3:
                os << get<unique_ptr<JSON_s>>(elem.second)->data;
                break;
        }
        sep = ", ";
    }
    return os << " }";
}

int main() {
    JSON obj;
    obj.emplace_back("a", make_unique<JSON_s>());
    obj.emplace_back("b", monostate{});
    obj.emplace_back("c", 1.2);
    obj.emplace_back("d", "Hi!"s);
    cout << obj << '\n';
}
