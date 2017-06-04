#ifndef SOCIAL_NETWORK_HPP
#define SOCIAL_NETWORK_HPP

#include <iostream>
#include <map>

#include "user.hpp"

using namespace std;

// This is the Graph (G) for the computation
class SocialNetwork {
public:
    // Starts a blank social network
    SocialNetwork();
    ~SocialNetwork();
    
    // The deadline constraint
    float deadline_contraint = 0;
    float total_time = 0;
    
    // Starts a social network loading a file
    SocialNetwork(string file);
    
    // Prints the social network on the terminal
    void print();
    
    // Finds the top influencer
    User* find_top_influencer();
    
    // Find the second top influencer
    User* find_second_top_influencer();
    
private:
    // Add data to a social network
    void load_data(string file);
    
    // Find the influence for a single user, returns the user
    void calculate_distances_for_user(User* src);
    
    // Find the influence for a calculated map
    float find_influence_for_user();
    
    // Marks the nodes that have been visited by top influencer
    void mark_deadline_distances();
    
    // Find the influence for a calculated map
    float find_influence_unvisited_for_user();
    
    // The users for the social network
    map<int,User> users;
    
    // A list to the top influencers
    map<int,User*> influencer_list;
    
    // Clocks to measure the time
    clock_t start_time;
    clock_t time_for_top_1;
    clock_t time_for_top_2;
};

#endif /* SOCIAL_NETWORK_HPP */

