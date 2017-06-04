#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <iostream>
#include <map>

#define FLOAT_MAX 3.402823e+38

using namespace std;

// The user is the node of the graph

class Node {
    friend class Graph;
    friend struct CompareNode;
private:
    bool visited = false;
    float distance = FLOAT_MAX;
    bool influenced = false;
public:
    unsigned id = 0;
    
    Node() {}
    Node(int id) : id(id) {}

    map<Node*, float> paths;
    void add_path(Node& node, float weight = 0);

    bool operator<(const Node &rhs);
    bool operator()(Node& s1, Node& s2);
    bool operator()(Node*& s1, Node*& s2);

    operator int() const {
        return id;
    }
    friend ostream& operator<<(ostream& os, const Node& u);
};

ostream& operator<<(ostream& os, const Node& u);

struct CompareNode {
    bool operator()(Node* &l, Node* &r) const {
        return l->distance > r->distance;
    }
};

#endif /* USER_HPP */

