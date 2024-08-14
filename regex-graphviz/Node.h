#ifndef Node_h
#define Node_h

#include <string>
#include <set>

class Node {
    std::string name;
    int id;
    std::set<int> edges;
public:
    Node(const std::string& name, int id) : name{ name }, id{ id } {}
    void addEdgeTo(int id) { edges.insert(id); }
    const auto& getName() const { return name; }
    int getId() const { return id; }
    const auto& getEdges() const { return edges; }
};

#endif