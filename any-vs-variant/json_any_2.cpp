// json_any_2.cpp : build and output more complex JSON object using std::any
// requires -std=c++17 or later

#include <any>
#include <utility>
#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <stdexcept>

using namespace std;
using JSON = vector<pair<string,any>>;
using JSONArray = vector<any>;

// note: this forward declaration is necessary
ostream& operator<< (ostream& os, const JSON& json);

ostream& operator<< (ostream& os, const JSONArray& json_array) {
    if (json_array.empty()) {
        return os << "[]";
    }
    auto sep = ""sv;
    os << "[ ";
    for (const auto& array_elem : json_array) {
        os << sep;
        if (array_elem.type() == typeid(void)) {
            os << "undefined";
        }
        else if (array_elem.type() == typeid(int)) {
            os << any_cast<int>(array_elem);
        }
        else if (array_elem.type() == typeid(double)) {
            os << any_cast<double>(array_elem);
        }
        else if (array_elem.type() == typeid(bool)) {
            os << (any_cast<bool>(array_elem) ? "true" : "false");
        }
        else if (array_elem.type() == typeid(string)) {
            os << '\'' << any_cast<string>(array_elem) << '\'';
        }
        else if (array_elem.type() == typeid(JSON)) {
            os << any_cast<JSON>(array_elem);
        }
        else if (array_elem.type() == typeid(JSONArray)) {
            os << any_cast<JSONArray>(array_elem);
        }
        else {
            throw runtime_error("JSON array element type not handled in operator<<");
        }
        sep = ", ";
    }
    return os << " ]";
}

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
        else if (elem.second.type() == typeid(int)) {
            os << any_cast<int>(elem.second);
        }
        else if (elem.second.type() == typeid(double)) {
            os << any_cast<double>(elem.second);
        }
        else if (elem.second.type() == typeid(bool)) {
            os << (any_cast<bool>(elem.second) ? "true" : "false");
        }
        else if (elem.second.type() == typeid(string)) {
            os << '\'' << any_cast<string>(elem.second) << '\'';
        }
        else if (elem.second.type() == typeid(JSON)) {
            os << any_cast<JSON>(elem.second);
        }
        else if (elem.second.type() == typeid(JSONArray)) {
            os << any_cast<JSONArray>(elem.second);
        }
        else {
            throw runtime_error("JSON element type not handled by operator<<");
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
    obj.emplace_back("e", JSONArray{ 1, 2.3, "array"s, any{}, JSON{}, JSONArray{} });
    try {
        cout << obj << '\n';
    }
    catch (const runtime_error& e) {
        cerr << "\nError: " << e.what() << '\n';
    }
}
