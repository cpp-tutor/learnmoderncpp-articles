#ifndef Node_h
#define Node_h

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <stdexcept>

class Node;

class Node {
public:
    enum class NodeType : char {
        None = '?',
        Start = 'S',
        Accept = 'A',
        Disjunct = '|', 
        Concatenate = '.',
        Star = '*',
        Question = '?',
        Plus = '+',
        Letter = 'z'
    };
    Node(NodeType type, int id = -1, const std::string& name = "")
        : type{ type }, id{ id },
            name{ name.empty() ? (std::string{} + std::to_underlying(type)) : name }
            {}
    void addEdgeTo(const std::shared_ptr<Node>& node) {
        if ((node->getType() != Node::NodeType::Letter)
            && (node->getType() != Node::NodeType::Accept)) {
                throw std::runtime_error("Cannot add edge to this node type.");
            }
        if (std::find_if(edges.begin(), edges.end(),
                [&node](const auto& n){ return n.lock() == node; }
            ) == edges.end()) {
            edges.push_back(node);
        }
    }
    const NodeType getType() const { return type; }
    int getId() const { return id; }
    const std::string getName() const {
        return name.empty() ? (std::string{} + std::to_underlying(type)) : name;
    }
    const auto& getEdges() const { return edges; }
    const auto& getFirst() const { return first; }
    const auto& getLast() const { return last; }
    bool isNullable() const { return nullable; }
    const std::shared_ptr<Node>& getLeft() const { return left; }
    const std::shared_ptr<Node>& getRight() const { return right; }

    static void appendUnique(std::vector<std::shared_ptr<Node>>& dest,
                             const std::vector<std::shared_ptr<Node>>& src) {
        for (const auto& item : src) {
            if (std::find(dest.begin(), dest.end(), item) == dest.end()) {
                dest.push_back(item);
            }
        }
    }

    static std::shared_ptr<Node> makeLetter(int id, const std::string& name) {
        auto node = std::make_shared<Node>(NodeType::Letter, id, name);
        node->nullable = false;
        node->first.push_back(node);
        node->last.push_back(node);
        return node;
    }

    static std::shared_ptr<Node> makeDisjunct(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        auto node = std::make_shared<Node>(NodeType::Disjunct);
        node->left = std::move(left);
        node->right = std::move(right);
        node->nullable = node->left->nullable || node->right->nullable;
        node->first = node->left->first;
        appendUnique(node->first, node->right->first);
        node->last = node->left->last;
        appendUnique(node->last, node->right->last);
        return node;
    }

    static std::shared_ptr<Node> makeConcat(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        auto node = std::make_shared<Node>(NodeType::Concatenate);
        node->left = std::move(left);
        node->right = std::move(right);
        for (const auto& u : node->left->last) {
            for (const auto& v : node->right->first) {
                u->addEdgeTo(v);
            }
        }
        node->nullable = node->left->nullable && node->right->nullable;
        node->first = node->left->first;
        if (node->left->nullable) {
            appendUnique(node->first, node->right->first);
        }
        node->last = node->right->last;
        if (node->right->nullable) {
            appendUnique(node->last, node->left->last);
        }
        return node;
    }

    static std::shared_ptr<Node> makeStar(std::shared_ptr<Node> child) {
        auto node = std::make_shared<Node>(NodeType::Star);
        node->left = std::move(child);
        for (const auto& u : node->left->last) {
            for (const auto& v : node->left->first) {
                u->addEdgeTo(v);
            }
        }
        node->nullable = true;
        node->first = node->left->first;
        node->last = node->left->last;
        return node;
    }

    static std::shared_ptr<Node> makePlus(std::shared_ptr<Node> child) {
        auto node = std::make_shared<Node>(NodeType::Plus);
        node->left = std::move(child);
        for (const auto& u : node->left->last) {
            for (const auto& v : node->left->first) {
                u->addEdgeTo(v);
            }
        }
        node->nullable = node->left->nullable;
        node->first = node->left->first;
        node->last = node->left->last;
        return node;
    }

    static std::shared_ptr<Node> makeQuestion(std::shared_ptr<Node> child) {
        auto node = std::make_shared<Node>(NodeType::Question);
        node->left = std::move(child);
        node->nullable = true;
        node->first = node->left->first;
        node->last = node->left->last;
        return node;
    }

    static std::shared_ptr<Node> makeStart(std::shared_ptr<Node> regex, int acceptId) {
        auto start = std::make_shared<Node>(NodeType::Start, 0);
        auto accept = std::make_shared<Node>(NodeType::Accept, acceptId);
        start->left = std::move(regex);
        start->right = accept;

        for (const auto& v : start->left->first) {
            start->addEdgeTo(v);
        }
        if (start->left->nullable) {
            start->addEdgeTo(accept);
        }
        for (const auto& u : start->left->last) {
            u->addEdgeTo(accept);
        }
        return start;
    }

    template<typename Callable>
    void visit(const Callable& c) {
        if (left != nullptr) {
            left->visit(c);
        }
        std::invoke(c, *this);
        if (right != nullptr) {
            right->visit(c);
        }
    }
private:
    NodeType type;
    int id;
    std::string name;
    bool nullable{ false };
    std::vector<std::shared_ptr<Node>> first;
    std::vector<std::shared_ptr<Node>> last;
    std::vector<std::weak_ptr<Node>> edges;
    std::shared_ptr<Node> left, right;
};

#endif