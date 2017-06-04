#include "graph.hpp"
#include "main.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <bitset>

Graph::Graph() {
}

Graph::~Graph() {
    for (unsigned i = 0; i < nodes.size(); i++)
        delete[] adjacency_matrix[i];
    delete[] adjacency_matrix;
}

Graph::Graph(string file) : Graph() {
    load_data(file);
}

void Graph::print() {
    cout << "Printing Graph" << endl;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        cout << "Node " << (*it).second.id << endl;
        for (auto jt = it->second.paths.begin(); jt != it->second.paths.end(); jt++) {
            cout << "  " << jt->first->id << " -> " << jt->second << endl;
        }
    }
}

void Graph::load_data(string file) {
    ifstream data_file(file, std::ifstream::in);
    if (!data_file.is_open()) {
        cout << "Could not open file: " << file << endl;
        exit(1);
    }
    else
        cout << "Loading data from " << file << endl;
    string line;

    stringstream ss;
    int node1;
    int node2;
    float weight;

    while (getline(data_file, line)) {
        ss << line;
        ss >> node1;
        ss >> node2;
        node1--;
        node2--;
        ss >> weight;
        ss.clear();
        if (DEBUG) cout << node1 << " " << node2 << " " << weight << endl;

        // Insert the nodes
        Node u1(node1);
        Node u2(node2);
        nodes.insert({node2, u2});
        nodes.insert({node1, u1});

        // Add the connections
        Node* u1p = &(nodes.find(node1)->second);
        Node* u2p = &(nodes.find(node2)->second);
        u1p->paths.insert({u2p, weight});
    }
    data_file.close();

    // Create the adjacency matrix
    int nodecount = this->nodes.size();
    adjacency_matrix = new float*[nodecount];
    for (int i = 0; i < nodecount; i++) {
        adjacency_matrix[i] = new float[nodecount];
        for (int j = 0; j < nodecount; j++) {
            adjacency_matrix[i][j] = -1;
        }
    }
}

// TODO debug this file and make sure it works

void Graph::dijkstra(Node* src) {
    vector<Node*> Q;

    // Initialization
    src->distance = 0;
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (&it->second != src) {
            it->second.distance = FLOAT_MAX;
            it->second.visited = false;
        }
    }
    Q.push_back(src);
    make_heap(Q.begin(), Q.end(), CompareNode());

    // Skip the loop if there are no connections

    // The main loop
    while (!Q.empty()) {
        Node* U = *(Q.begin());
        pop_heap(Q.begin(), Q.end());
        Q.pop_back();

        for (auto V = U->paths.begin(); V != U->paths.end(); V++) {
            float alt = U->distance + V->second;
            if (alt < V->first->distance) {
                V->first->distance = alt;
                Q.push_back(V->first);
            }
            V->first->visited = true;
        }
        sort_heap(Q.begin(), Q.end());
    }

    // TODO Mark the distances
    //  Fill in the adjacency matrix with all the distances for each of the nodes
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        //cout << src->id << " " << it->second.id << endl;
        adjacency_matrix[src->id][it->second.id] = it->second.distance;
    }
}

// TODO Loop through all the nodes and call the Djiktra function

void Graph::all_dijkstra() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        dijkstra(&it->second);
    }
}

void Graph::get_adjacency_matrix() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        for (auto it2 = nodes.begin(); it2 != nodes.end(); it2++) {

            float dist = 0;
            if (it == it2) dist = 0;
            else if (it->second.paths.find(&it2->second) == it->second.paths.end()) dist = -1;
            else dist = it->second.paths.find(&it2->second)->second;

            adjacency_matrix[it->second.id][it2->second.id] = dist;
        }
    }
}

void Graph::print_adjacency_matrix() {
    int nodecount = nodes.size();
    cout << "Adjacency Matrix" << endl;
    cout << "     ";
    for (int i = 0; i < nodecount; i++) {
        cout << "    " << i;
    }
    cout << endl;

    for (int i = 0; i < nodecount; i++) {
        cout << i << "    ";
        for (int j = 0; j < nodecount; j++) {
            cout << setw(5) << setprecision(3) << ((adjacency_matrix[i][j] > 100000000) ? -1 : adjacency_matrix[i][j]) << setw(0);
        }
        cout << endl;
    }
    cout << endl;
}

// TODO Uses the adjacency matrix to find the shortest path and then return

Path Graph::traveling_salesman_greedy(unsigned start_n) {
    Path p(this);
    // Use 0 as the starting node
    Node* start = &nodes[start_n];
    p.push_back(start);

    // Find the closest node using the adjacency matrix and set that as the start, then find the next one. return 
    unordered_set<int> visited;
    visited.insert(start_n);

    unsigned node_count = nodes.size();
    Node* curr = start;
    while (visited.size() < node_count) {
        float current_closest = FLOAT_MAX;
        int curr_closest_id = -1;

        for (unsigned i = 0; i < node_count; i++) {

            // Already found
            if (visited.find(i) != visited.end()) continue;
            if (i == curr->id) continue;

            // Update the next closest
            float newdist = adjacency_matrix[curr->id][i];
            if (newdist < current_closest) {
                current_closest = newdist;
                curr_closest_id = i;
            }
        }

        if (curr_closest_id == -1) {
            cout << "Graph is not completely connected, TSP cannot be solved" << endl;
            break;
        }

        p.push_back(&nodes[curr_closest_id]);
        visited.insert(curr_closest_id);
        curr = &nodes[curr_closest_id];
    }

    p.push_back(&nodes[start_n]);
    cout << p << endl;
    return p;
}

// TODO Returns a path of nodes via a vector. Needs to find the shortest path among ALL nodes using the Held Karps algorithm
// https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm
//    function algorithm TSP (G, n)
//        for k := 2 to n do
//          C({1, k}, k) := d1,k
//        end for
//
//        for s := 3 to n do
//          for all S ⊆ {1, 2, . . . , n}, |S| = s do
//            for all k ∈ S do
//              {C(S, k) = minm≠1,m≠k,m∈S [C(S − {k}, m) + dm,k ]}
//            end for
//          end for
//        end for
//
//        opt := mink≠1 [C({2, 3, . . . , n}, k) + dk,1]
//        return (opt)
//      end

typedef map<uint64_t, map<unsigned, pair<float, unsigned>>> PermutationMap;

PermutationMap get_all_permutations(unsigned n, unsigned start_n) {
    PermutationMap S;

    for (unsigned s = 0; s <= n; s++) {
        std::vector<bool> v(n);
        std::fill(v.begin(), v.begin() + s, true);

        do {
            uint64_t hash = 0;
            for (unsigned i = 0; i < n; ++i)
                if (v[i])
                    hash += 1 << i;
            if ((hash >> start_n) % 2 == 1) continue;

            uint64_t temp = hash;
            for (unsigned i = 0; i < n; ++i) {
                if (temp % 2 == 1) {
                    temp = temp >> 1;
                    continue;
                }
                temp = temp >> 1;
                if (i == start_n) continue;

                S[hash][i].first = 0;
            }
        } while (std::prev_permutation(v.begin(), v.end()));
    }

    uint64_t f = 0;
    for (unsigned i = 0; i < n; i++)
        if (i != start_n)
            f += 1 << i;
    S[f][start_n].first = 0;

    return S;
}

Path Graph::traveling_salesman(unsigned start_n) {
    unsigned n = nodes.size();
    PermutationMap g = get_all_permutations(n, start_n);
    unsigned hash = 0;

    for (unsigned k = 0; k < n; k++) {
        if (k == start_n) continue;
        g[hash][k].first = adjacency_matrix[k][start_n];
    }

    //cout << "Performing TSP" << endl;
    for (unsigned s = 1; s < n; s++) {
        //cout << s << endl;
        for (auto it = g.begin(); it != g.end(); it++) {
            if (bitset<64>(it->first).count() != s) continue;
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                //cout << bitset<8>(it->first) << " " << it2->first << endl;

                float min = FLOAT_MAX;
                int successor = -1;
                uint64_t tmp = it->first;
                for (unsigned i = 0; i < n; i++) {
                    if (tmp % 2 == 0) {
                        tmp = tmp >> 1;
                        continue;
                    }

                    //cout << it2->first << " " << i << endl;
                    float new_min = adjacency_matrix[it2->first][i] + g[it->first - (1 << i)][i].first;
                    if (min > new_min) {
                        min = new_min;
                        successor = i;
                    }
                    tmp = tmp >> 1;
                }
                it2->second.first = min;
                it2->second.second = successor;
                //cout << "  " << it2->second.first << "  " << it2->second.second << endl;
            }
        }
    }
    
//    for (auto it = g.begin(); it != g.end(); it++) {
//        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
//            cout << bitset<16>(it->first) << " " << it2->first << " " << it2->second.first << endl;
//        }
//    }
    
    //cout << "Backtracking the path" << endl;
    Path p(this);
    p.push_back(&nodes[start_n]);
    
    unsigned f = 0;
    for (unsigned i = 0; i < n; i++)
        f += 1 << i;

    unsigned successor = 0;
    
    while (f != 0) {
        //cout << successor << " -> ";
        f = f - (1 << successor);
        //cout << bitset<8>(f) << " " << successor << endl;
        successor = g[f][successor].second;
        p.push_back(&nodes[successor]);
    }
    
    cout << p << endl;
    return p;
}