#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <chrono>

#include "main.hpp"
#include "graph.hpp"

using namespace std;

void usage() {
    cout << "Usage: tsp <filename> <deadline_contraint>" << endl;
    cout << "       tsp -g <filename> <nodecount> <density> <seed>" << endl;
    exit(1);
}

void generate_graph(char* output_file, int nodecount, int density, int seed) {
    srand(seed);
    cout << "Generating Graph - Nodecount: " << nodecount << " Density: " << density << endl;

    if (nodecount <= 0) {
        cerr << "Invalid Node Count" << endl;
        exit(1);
    }

    ofstream fs(output_file);

    if (!fs) {
        cerr << "Cannot open the file " << output_file << endl;
        exit(1);
    }

    int p1, p2;
    float weight;
    for (int i = 0; i < nodecount * density; i++) {
        p1 = rand() % nodecount + 1;
        p2 = rand() % nodecount + 1;
        weight = ((float) (rand() % 10000)) / 1000;
        fs << p1 << " " << p2 << " " << weight << endl;
        fs << p2 << " " << p1 << " " << weight << endl;
    }

    fs.close();
    exit(1);
}

void write_result_to_dat_file(double millis) {
    ofstream fs("test/data.dat", fstream::app);
    
    if (!fs) {
        cerr << "Cannot open the file " << "test/data.dat" << endl;
        exit(1);
    }
    fs << millis << endl;
    fs.close();
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 6) usage();
    if (argc == 6) {
        if(strcmp(argv[2], "-g") == 0) usage();
        stringstream ss;
        int nodecount;
        int density;
        int seed;
        
        ss << argv[3];
        ss >> nodecount;
        ss.clear();
        ss << argv[4];
        ss >> density;
        ss.clear();
        ss << argv[5];
        ss >> seed;
        ss.clear();
        
        generate_graph(argv[2], nodecount, density, seed);
    }
    char* filename = argv[1];

    // Loads the graph application with the file
    auto start = chrono::high_resolution_clock::now();
    
    Graph graph(filename);
    //graph.print();
    //cout << "Calculating Adjacency Matrix" << endl;
    graph.all_dijkstra();
    //graph.print_adjacency_matrix();
    //cout << "Computing Shortest Path" << endl;
    graph.traveling_salesman((unsigned) 0);
    
    auto end = chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> diff = end-start;
    std::cout << "Total Time Elapsed "  << diff.count() << " s\n";
    write_result_to_dat_file(diff.count());
    return 1;
}
