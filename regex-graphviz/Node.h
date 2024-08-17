#ifndef Node_h
#define Node_h

#include <string>
#include <vector>
#include <list>
#include <algorithm>

class Node {
    std::string name;
    int id;
    std::vector<std::list<Node>::iterator> edges;
public:
    Node(const std::string& name, int id) : name{ name }, id{ id } {}
    void addEdgeTo(std::list<Node>::iterator& node) {
        if (std::find(edges.begin(), edges.end(), node) == edges.end()) {
            edges.push_back(node);
        }
    }
    void removeEdgeTo(std::list<Node>::iterator& node) {
        if (auto iter = std::find(edges.begin(), edges.end(), node); iter != edges.end()) {
            edges.erase(iter);
        }
    }
    void setName(const std::string& n) { name = n; }
    const auto& getName() const { return name; }
    int getId() const { return id; }
    const auto& getEdges() const { return edges; }
};

#endif