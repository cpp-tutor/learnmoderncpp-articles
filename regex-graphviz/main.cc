#include "Scanner.h"
#include "Parser.h"
#include "Node.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

int main() {
    std::cout << "Please enter a regex, or blank line to end:\n";
    for (;;) {
        std::string str;
        getline(std::cin, str);
        if (str.empty()) {
            return 0;
        }
        std::istringstream input(str);
        std::vector<Node> nodes;
        Scanner scanner(input);
        Parser parser(scanner, nodes);
        if (!parser.parse()) {
            std::cout << "digraph regex {\n  label=\"" << str << "\";\n  rankdir=LR;\n  node [shape=circle];\n\n";
            for (const auto& node : nodes) {
                std::cout << "  q" << node.getId() << " [label=\"";
                std::cout << node.getName();
                std::cout << "\"];\n";
            }
            std::cout << '\n';
            for (const auto& node : nodes) {
                for (const auto& edge : node.getEdges()) {
                    std::cout << "  q" << node.getId() << " -> q" << edge << " [label=\"";
                    if (nodes.at(edge).getName().size() == 1) {
                        std::cout << nodes.at(edge).getName();
                    }
                    else {
                        std::cout << "ε";
                    }
                    std::cout << "\"";
                    if (node.getId() == edge) {
                        std::cout << " dir=back";
                    }
                    std::cout << "];\n";
                }
            }
            std::cout << "}\n";
        }
    }
}
