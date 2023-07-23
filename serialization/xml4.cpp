#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <regex>
#include <exception>
#include <algorithm>
#include <memory>
#include <utility>
#include <cctype>
#include <sstream>

class XMLError : public std::exception {
    std::string str;
public:
    XMLError(std::string_view s) : str{ s } {}
    const char *what() const noexcept override { return str.c_str(); }
};

class XMLElement;

class XMLElement {
    std::string name, value;
    std::vector<std::pair<std::string,std::string>> attributes;
    std::vector<std::unique_ptr<XMLElement>> children;
    const std::string_view indent_with = "  ";
    static std::string read_until(std::istream &is, char c, bool eat, bool skipws) {
        std::string str;
        auto ch = is.get();
        while (!is.eof() && (static_cast<char>(ch) != c)) {
            if (!skipws || ch > ' ') {
                str += static_cast<char>(ch);
            }
            ch = is.get();
        }
        if (eat) {
            if (!skipws || ch > ' ') {
                str += static_cast<char>(ch);
            }
        }
        else {
            is.putback(ch);
        }
        return str;
    }
public:
    XMLElement(std::string_view name, std::string_view value)
        : name{ name }, value{ value } {}
    XMLElement(
        std::string_view name,
        std::vector<std::pair<std::string,std::string>>&& attributes = {}
    ) : name{ name }, attributes{ std::move(attributes) } {}
    XMLElement(std::istream& is) {
        std::string str;
        str = read_until(is, '<', false, true);
        if (str.empty()) {
            str = read_until(is, '>', true, false);
            const std::regex begin_elem{ R"(<([A-Za-z_][A-Za-z0-9_]*)((\n|\r|.)*)>)" },
                end_elem{ R"((/>)|(</([A-Za-z_][A-Za-z0-9_]*)>))" },
                attr{ R"*(^\s+([A-Za-z_][A-Za-z0-9_]*)="([^"]*)")*" }, end_attrs{ R"(\s*/?$)" };
            std::smatch matches;
            if (std::regex_match(str, matches, begin_elem)) {
                name = matches[1].str();
                str = matches[2].str();
                if (!str.empty()) {
                    std::smatch attrs;
                    while (std::regex_search(str, attrs, attr)) {
                        attributes.emplace_back(attrs[1].str(), attrs[2].str());
                        str = str.substr(attrs[0].str().size());
                    }
                    if (!std::regex_match(str, end_attrs)) {
                        throw XMLError("Expected attribute instead of: " + str);
                    }
                }
                if (str.back() == '/') {
                    return;
                }
                str = read_until(is, '<', false, false);
                if (std::find_if(str.cbegin(), str.cend(), [](char c){ return c > ' '; }) != str.cend()) {
                    value = str;
                    str = read_until(is, '>', true, false);
                    if (std::regex_match(str, matches, end_elem)) {
                        if (matches[3].str() == name) {
                            return;
                        }
                    }
                }
                else {
                    for (;;) {
                        children.push_back(std::make_unique<XMLElement>(is));
                        str = read_until(is, '<', true, true);
                        if (str != "<") {
                            break;
                        }
                        char c;
                        is >> c;
                        if (c == '/') {
                            str = "</" + read_until(is, '>', true, false);
                            if (std::regex_match(str, matches, end_elem)) {
                                if (matches[3].str() == name) {
                                    return;
                                }
                            }
                            break;
                        }
                        is.putback(c);
                        is.putback('<');
                    }
                }
            }
        }
        throw XMLError("Bad input: " + str);
    }
    void addChild(std::unique_ptr<XMLElement> child) {
        children.emplace_back(std::move(child));
    }
    void serialize(std::ostream& os, int indent = 0) const {
        for (int i = 0; i != indent; ++i) {
            os << indent_with;
        }
        os << '<' << name;
        for (const auto& a : attributes) {
            os << ' ' << a.first << "=\"" << a.second << "\"";
        }
        if (children.empty()) {
            if (value.empty()) {
                os << " />\n";
            }
            else {
                os << '>' << value << "</" << name << ">\n";
            }
        }
        else {
            os << ">\n";
            for (const auto& c : children) {
                c->serialize(os, indent + 1);
            }
            for (int i = 0; i != indent; ++i) {
                os << indent_with;
            }
            os << "</" << name << ">\n";
        }
    }
    const XMLElement& operator[](size_t idx) const {
        if (idx >= children.size()) {
            throw XMLError("Index " + std::to_string(idx)
                + " out of range for element: " + name);
        }
        return *children[idx];
    }
    const std::string& operator[](std::string_view idx) const {
        auto iter1 = std::find_if(attributes.cbegin(), attributes.cend(),
            [&idx](const auto& attr){ return idx == attr.first;
        });
        if (iter1 != attributes.cend()) {
            return iter1->second;
        }
        auto iter2 = std::find_if(children.cbegin(), children.cend(),
            [&idx](const auto& child){ 
                return idx == child->name && !child->value.empty();
            });
        if (iter2 != children.cend()) {
            return (*iter2)->value;
        }
        throw XMLError("No such attribute or leaf child name "
            + std::string{ idx } + " for element: " + name);
    }
    const std::string& elementName() const {
        return name;
    }
    size_t numberOfAttributes() const {
        return attributes.size();
    }
    size_t numberOfChildren() const {
        return children.size();
    }
    const std::vector<std::string> getAttributeNames() const {
        std::vector<std::string> attrs;
        std::for_each(attributes.cbegin(), attributes.cend(),
            [&attrs](const auto& attr){ attrs.push_back(attr.first);
        });
        return attrs;
    }
    const std::vector<std::string> getChildNames() const {
        std::vector<std::string> childNames;
        std::for_each(children.cbegin(), children.cend(),
            [&childNames](const auto& child){
                childNames.push_back(child->name);
            });
        return childNames;
    }
};

class Person {
    int id;
    std::string name;
    unsigned age;
    std::string location;
public:
    Person(int id, std::string_view name,
        unsigned age, std::string_view location)
        : id{ id }, name{ name }, age{ age }, location{ location } {}
    std::unique_ptr<XMLElement> to_xml() const {
        auto xml_tree = std::make_unique<XMLElement>("Person",
            std::vector<std::pair<std::string,std::string>>
            { { "id", std::to_string(id) } });
        xml_tree->addChild(std::make_unique<XMLElement>("Name", name));
        xml_tree->addChild(std::make_unique<XMLElement>("Age",
             std::to_string(age)));
        xml_tree->addChild(std::make_unique<XMLElement>("Location", location));
        return xml_tree;
    }
};

class People {
    std::vector<Person> people;
public:
    People(const XMLElement& root) {
        if (root["version"] == "v0") {
            for (int c = 0; c != root.numberOfChildren(); ++c) {
                people.emplace_back(Person(
                    std::stoi(root[c]["id"]),
                    root[c]["Name"],
                    std::stoi(root[c]["Age"]),
                    root[c]["Location"]
                ));
            }
        }
    }
    People() = default;
    void add(Person&& person) {
        people.emplace_back(std::move(person));
    }
    std::unique_ptr<XMLElement> to_xml() const {
        auto xml_tree = std::make_unique<XMLElement>("People",
            std::vector<std::pair<std::string,std::string>>
            { { "version", "v0" } });
        for (auto& p : people) {
            xml_tree->addChild(p.to_xml());
        }
        return xml_tree;
    }
};

int main() {
    std::vector<Person> pp{ { 41, "Alice", 25, "New York" },
        { 42, "Bob", 30, "Los Angeles" },
        { 43, "Charlie", 35, "Detroit" } };
    People crowd;
    for (auto p : pp) {
        crowd.add(std::move(p));
    }
    std::stringstream strstrm;
    crowd.to_xml()->serialize(strstrm);
    try {
        XMLElement XML(strstrm);
        People other(XML);
        other.to_xml()->serialize(std::cout);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
