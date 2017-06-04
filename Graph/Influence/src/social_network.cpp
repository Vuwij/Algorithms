#include "social_network.hpp"
#include "constants.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <queue>


SocialNetwork::SocialNetwork() {
    start_time = clock();
}

SocialNetwork::~SocialNetwork() {
}

SocialNetwork::SocialNetwork(string file) : SocialNetwork() {
    load_data(file);
}

void SocialNetwork::print() {
    cout << "Printing Graph" << endl;
    for(auto it = users.begin(); it != users.end(); ++it)
        cout << (*it).second << endl;
}

void SocialNetwork::calculate_distances_for_user(User* src) {
    vector<User*> Q;
    
    // Initialization
    src->distance = 0;
    for(auto it = users.begin(); it != users.end(); it++) {
        if(&it->second != src) {
            it->second.distance = FLOAT_MAX;
            it->second.visited = false;
        }
    }
    Q.push_back(src);
    make_heap(Q.begin(), Q.end(), UserComp());
    
    // Skip the loop if there are no connections
    if(src->connections.empty()) return;
    
    // The main loop
    while(!Q.empty()) {
        User* U = *(Q.begin());
        pop_heap(Q.begin(), Q.end()); Q.pop_back();
        
        for(auto V = U->connections.begin(); V != U->connections.end(); V++) {
            float alt = U->distance + V->weight;
            if(alt < V->connected_user->distance) {
                V->connected_user->distance = alt;
                if(alt <= deadline_contraint) {
                    Q.push_back(V->connected_user);
                }
            }
            V->connected_user->visited = true;
        }
        sort_heap(Q.begin(), Q.end());
    }
}

float SocialNetwork::find_influence_for_user() {
    float total_influence = 0;
    //if(DEBUG) cout << " [";
    for(auto it = users.begin(); it != users.end(); it++) {
        if(it->second.distance <= deadline_contraint) {
            //if(DEBUG) cout <<  it->second.id << ", ";
            total_influence ++;
        }
    }
    //if(DEBUG) cout << "]";
    return total_influence;
}

float SocialNetwork::find_influence_unvisited_for_user() {
    float total_influence = 0;
    for(auto it = users.begin(); it != users.end(); it++) {
        if(!it->second.influenced) {
            if(it->second.distance <= deadline_contraint) {
                total_influence ++;
            }
        }
    }
    return total_influence;
}

void SocialNetwork::mark_deadline_distances() {
    for(auto it = users.begin(); it != users.end(); it++)
        if(it->second.distance <= deadline_contraint)
            it->second.influenced = true;
}

User* SocialNetwork::find_top_influencer() {
    float max_influence = 0;
    User* max_influence_user;
    
    if(DEBUG) cout << "Finding Top influencer" << endl;
    for(auto it = users.begin(); it != users.end(); it++) {
        calculate_distances_for_user(&it->second);
        it->second.influence = find_influence_for_user();
        if(it->second.influence > max_influence) {
            max_influence = it->second.influence;
            max_influence_user = &(it->second);
        }
        if(DEBUG) cout << "Node " << it->second.id << " : " << it->second.influence << endl;
    }
    
    return max_influence_user;
}

User* SocialNetwork::find_second_top_influencer() {
    User* top_influencer = find_top_influencer();
    calculate_distances_for_user(top_influencer);
    mark_deadline_distances();
    time_for_top_1 = clock();
    
    float max_influence = 0;
    User* second_influencer;
    if(DEBUG) cout << "Finding Second Top influencer" << endl;
    for(auto it = users.begin(); it != users.end(); it++) {
        if(it->second.id == top_influencer->id) continue;
        calculate_distances_for_user(&it->second);
        it->second.influence = find_influence_unvisited_for_user();
        if(it->second.influence > max_influence) {
            max_influence = it->second.influence;
            second_influencer = &(it->second);
        }
        if(DEBUG) cout << "Node " << it->second.id << " : " << it->second.influence << endl;
    }
    time_for_top_2 = clock();
    
    double top_1_duration = (time_for_top_1 - start_time)/ (double) CLOCKS_PER_SEC;
    double top_2_duration = (time_for_top_2 - start_time)/ (double) CLOCKS_PER_SEC;
    total_time = top_2_duration;
    cout << "TOP-1 INFLUENCER: " << top_influencer->id << ", SPREAD:  " << top_influencer->influence << ", TIME: "<< top_1_duration << endl;
    cout << "TOP-2 INFLUENCER: " << second_influencer->id << ", MARGINAL SPREAD:  " << second_influencer->influence << ", TIME: "<< top_2_duration << endl;
    return second_influencer;
}

void SocialNetwork::load_data(string file) {
    ifstream data_file(file, std::ifstream::in);
    if (!data_file.is_open()) 
        cout << "Could not open file: " << file << endl;
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
        ss >> weight;
        ss.clear();
        if(DEBUG) cout << node1 << " " << node2 << " " << weight << endl;
        
        // Insert the nodes
        User u1(node1);
        User u2(node2);
        users.insert({node2, u2});
        users.insert({node1, u1});
        
        // Add the connections
        User* u1p = &(users.find(node1)->second);
        User* u2p = &(users.find(node2)->second);
        u1p->add_connection(u2p, weight);
    }
    data_file.close();
}