#include <iomanip>
#include <map>

#include "node.hpp"

void Node::add_path(Node& node, float weight) {
    this->paths.insert({&node, weight});
}

bool Node::operator <(const Node &rhs) {
    return this->distance < rhs.distance;
}

bool Node::operator()(Node& s1, Node& s2) {
    return s1.distance < s2.distance;
}

bool Node::operator()( Node*& s1, Node*& s2) {
    return s1->distance < s2->distance;
}

ostream& operator<<(ostream& os, const Node& u) {
    os << "Node " << u.id << " - " << u.paths.size() << " connections" << endl;
    for(auto it = u.paths.begin(); it != u.paths.end(); it++) {
        os << it->first->id << "\t  " << it->second << endl;
    } 
    return os;
}