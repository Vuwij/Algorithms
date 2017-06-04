/* 
 * File:   main.cpp
 * Author: Jason Wang
 *
 * Created on June 18, 2016, 12:27 PM
 */

#include "main.h"
#include "Node.h"
#include "algorithms.h"

#include <set>
#include <unordered_map>

using namespace std;

unordered_map<int, Node> NodeMap;
std::set<int> max_clique;

int main(int argc, char** argv) {
    
    // Loading the textual files as command line argument
    cout << "Loading World" << endl;
    
    if(argc != 3) {
        cout << "The number or arguments is incorrect" << endl;
        return 0;
    }
    
    nodeFile = argv[1];
    edgeFile = argv[2];
    
    auto t1 = chrono::high_resolution_clock::now();
    loadNodesFromFile("World/" + nodeFile);
    loadEdgesFromFile("World/" + edgeFile);
        
    auto t2 = chrono::high_resolution_clock::now();
    
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(t2 - t1);
    cout << "File loading time: " << std::setprecision(5) << time_span.count() << " seconds" << endl;
    
    // Display on the map
    //mainGL(argc, argv);
    
    // Start searching for the maximum clique problem
    cout << "Starting search for maximum clique" << endl;
    
    // Time how long it takes to do the search
    auto t3 = chrono::high_resolution_clock::now();
    findMaximumClique();
    auto t4 = chrono::high_resolution_clock::now();
    
    chrono::duration<double> time_span_2 = chrono::duration_cast<chrono::duration<double> >(t4 - t3);
    cout << "Maximum clique search time: " << std::setprecision(5) << time_span_2.count() << " seconds" << endl;
    
    return 0;
}

void loadNodesFromFile(string file) {
    ifstream fStream;
    fStream.exceptions (std::ifstream::failbit | std::ifstream::badbit );
    
    file += "";
    
    // The type of nodes and edges to parse
    int nodeID = 0;
    string nodeType = "";
    
    try {
        fStream.open (file);
        while (!fStream.eof()) {
            fStream >> nodeID >> nodeType;
            // Process the file
            NodeMap.emplace(nodeID, Node(nodeID, nodeType));
        }
        printEntireMap();
    } catch (ifstream::failure e) {
        if(fStream.eof()) {
            fStream.close();
            
            return;
        }
        
        std::cout << "Error while reading file: " << file << endl;
        std::cout << e.what();
        exit (EXIT_FAILURE);
    }
}

void loadEdgesFromFile(string file) {
    ifstream fStream;
    
    fStream.exceptions (std::ifstream::failbit | std::ifstream::badbit );
    
    // The type of nodes and edges to parse
    char e;
    int from = 0;
    int to = 0;
    string type = "";
    
    try {
        fStream.open (file);
        
        while (!fStream.eof()) {
            fStream >> e >> from >> to >> type;
            // Process the file
            
            NodeMap[from].addNeighbours(to, type);
            NodeMap[to].addNeighbours(from, type);
        }
        
        fStream.close();
        
    } catch (ifstream::failure e) {
        if(fStream.eof()) return;
        
        std::cout << "Error while reading file: " << file << endl;
        std::cout << e.what();
        exit (EXIT_FAILURE);
    }
}

void visualizeNodesAndEdges() {
    
}

void printEntireMap() {
    for(int i = 0; i < NodeMap.size(); i++) {
        NodeMap[i].print();
    }
}

void findMaximumClique() {
    if(PRINT_VALUES) printEntireMap();
    
    for(int i = 1; i < NodeMap.size(); i++) {
        P.insert(NodeMap[i].id);
    }
    
    Bron_kerbosch(P, R, X);
    
    cout << "Maximum Clique Size: " << currentMax.size() << endl;
    cout << "Clique contains: ";
    printGroup(currentMax);
    cout << endl;
}