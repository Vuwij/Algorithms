#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <iostream>

#include "node.hpp"
#include "graph.hpp"

using namespace std;

class Graph;
class Path : public vector<Node*> {
private:
    Graph* g;
public:
    Path(Graph* g) : g(g) {}
    void print();
    float get_total_length() const;
    friend ostream& operator<<(ostream& os, const Path& u);
};

ostream& operator<<(ostream& os, const Path& u);

#endif /* PATH_HPP */

