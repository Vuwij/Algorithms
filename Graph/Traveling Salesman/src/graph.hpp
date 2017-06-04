#ifndef SOCIAL_NETWORK_HPP
#define SOCIAL_NETWORK_HPP

#include <iostream>
#include <map>
#include <time.h>

#include "node.hpp"
#include "path.hpp"

using namespace std;

// This is the Graph (G) for the computation
class Path;
class Graph {
private:
    // Add data to a social network
    void load_data(string file);

    // The users for the social network
    map<int, Node> nodes;

public:
    // Starts a blank social network
    Graph();
    ~Graph();

    // Starts a social network loading a file
    Graph(string file);

    // Prints the social network on the terminal
    void print();

    // Finds the djisktra from a node
    void dijkstra(Node* t);
    void all_dijkstra();

    // The adjacency matrix
    float** adjacency_matrix;
    void get_adjacency_matrix();
    void print_adjacency_matrix();

    // Traveling salesman solutions
    Path traveling_salesman_greedy(unsigned start_n);
    Path traveling_salesman(unsigned start_n);
};

#endif /* SOCIAL_NETWORK_HPP */

