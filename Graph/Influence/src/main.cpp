#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include "main.hpp"
#include "social_network.hpp"
#include "constants.hpp"

using namespace std;

void usage() {
    cout << "Usage: influence <filename> <deadline_contraint>" << endl;
    cout << "       influence -g <filename> <nodecount> <density> <seed>" << endl;
    exit(1);
}

void generate_graph(char* output_file, int nodecount, float density, int seed) {
    srand(seed);

    if (nodecount <= 0) {
        cerr << "Invalid Node Count" << endl;
        exit(1);
    }

    ofstream fs(output_file);

    if (!fs) {
        cerr << "Cannot open the file " << output_file << endl;
        exit(1);
    }

    for (int i = 0; i < nodecount * density; i++) {
        fs << rand() % nodecount << " " << rand() % nodecount << " " << ((float) (rand() % 10000)) / 1000 << endl;
    }

    fs.close();
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 6) usage();
    if (argc == 6) {
        if(strcmp(argv[2], "-g") == 0) usage();
        generate_graph(argv[2], stoi(argv[3]), stof(argv[4]), stoi(argv[5]));
    }
    char* filename = argv[1];
    float deadline_contraint = atof(argv[2]);

    // Loads the graph application
    SocialNetwork social_network(filename);
    social_network.deadline_contraint = deadline_contraint;
    //social_network.print();

    // These parts you still have to implement the algorithm
    social_network.find_second_top_influencer();
    
    // Return in microseconds
    int total_time_in_us = social_network.total_time * 1000;
    cout << "Total Time (in us) " << total_time_in_us << endl;
    return total_time_in_us/10;
}
