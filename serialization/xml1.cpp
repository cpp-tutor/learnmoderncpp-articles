#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <utility>
#include <cctype>

class XMLElement;

class XMLElement {
    std::string name, value;
    std::vector<std::pair<std::string,std::string>> attributes;
    std::vector<std::unique_ptr<XMLElement>> children;
    const std::string_view indent_with = "  ";
public:
    XMLElement(std::string_view name, std::string_view value)
        : name{ name }, value{ value } {}
    XMLElement(
        std::string_view name,
        std::vector<std::pair<std::string,std::string>>&& attributes = {}
    ) : name{ name }, attributes{ std::move(attributes) } {}
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
};

int main() {
    const char *fields[] = { "Name", "Age", "Location" },
        *data[] = { "Alice", "25", "New York",
            "Bob", "30", "Los Angeles", 
            "Charlie", "35", "Detroit",
            ""
        };

    XMLElement use_attr("People");

    for (auto p = data; **p;) {
        std::vector<std::pair<std::string,std::string>> attrs;
        for (int f = 0; f != 3; ++f) {
            std::string field = fields[f];
            field.front() = tolower(field.front());
            attrs.emplace_back(std::pair<std::string,std::string>{ field, *p++ });
        }
        use_attr.addChild(std::make_unique<XMLElement>("Person", std::move(attrs)));
    }
        
    use_attr.serialize(std::cout);
    
    XMLElement no_use_attr("People");
    
    for (auto p = data; **p;) {
        auto person = std::make_unique<XMLElement>("Person");
        for (int f = 0; f != 3; ++f) {
            person->addChild(std::make_unique<XMLElement>(fields[f], *p++));
        }
        no_use_attr.addChild(std::move(person));
    }
    
    no_use_attr.serialize(std::cout);
}
