#include "Node.h"
#include "Scanner.h"
#include "Parser.h"
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
        std::list<Node> nodes;
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
                    std::cout << "  q" << node.getId() << " -> q" << edge->getId() << " [label=\"";
                    if (edge->getName().size() == 1) {
                        std::cout << edge->getName();
                    }
                    else {
                        std::cout << "ε";
                    }
                    std::cout << "\"";
                    if (node.getId() == edge->getId()) {
                        std::cout << " dir=back";
                    }
                    std::cout << "];\n";
                }
            }
            std::cout << "}\n";
        }
    }
}
