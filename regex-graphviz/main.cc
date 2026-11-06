#include "Node.h"
#include "Scanner.h"
#include "Parser.h"
#include <sstream>
#include <iostream>

int main(const int argc, const char **argv) {
    std::cout << "Please enter a regex, or blank line to end:\n";
    for (;;) {
        std::string str;
        getline(std::cin, str);
        if (str.empty()) {
            return 0;
        }
        std::istringstream input(str);
        std::shared_ptr<Node> tree;
        Scanner scanner(input);
        Parser parser(scanner, tree);
        if (!parser.parse()) {
            std::cout << "digraph regex {\n  graph [label=\"" 
                << str << "\", root=q" << tree->getId()
                << ",  rankdir=LR, ranksep=0.6]\n"
                << "  node [shape=circle, fixedsize=true, width=0.4];\n\n";
            tree->visit(
                [](const Node& node){
                    if ((node.getType() == Node::NodeType::Letter)
                        || (node.getType() == Node::NodeType::Empty)
                        || (node.getType() == Node::NodeType::Start)
                        || (node.getType() == Node::NodeType::Accept)) {
                            std::cout << "  q" << node.getId() << " [label=\"";
                            std::cout << node.getName() << "\"";
                            if ((node.getType() == Node::NodeType::Start)
                                || (node.getType() == Node::NodeType::Accept)) {
                                    std::cout << ", peripheries=2";
                            }
                            std::cout << "];\n";
                    }
                }
            );
            std::cout << '\n';
            tree->visit(
                [](const Node& node){
                    for (const auto& edge : node.getEdges()) {
                        std::shared_ptr<Node> target = edge.lock();
                        std::cout << "  q" << node.getId() << " -> q" << target->getId() << " [label=\"";
                        if (target->getType() == Node::NodeType::Letter) {
                            std::cout << target->getName();
                        }
                        else {
                            std::cout << "ε";
                        }
                        std::cout << "\"";
                        if (node.getId() == target->getId()) {
                            std::cout << ", dir=back";
                        }
                        std::cout << "];\n";
                    }
                }
            );
            std::cout << "}\n";
        }
    }
}
