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
};

int main() {
    try {
        XMLElement xml_doc(std::cin);
        xml_doc.serialize(std::cout);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
