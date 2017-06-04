#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "sort.hpp"
#include "reddit_info.hpp"

using namespace std;

int stoi(string s) {
    stringstream ss;
    ss << s;
    int i;
    ss >> i;
    return i;
}

vector<RedditInfo> import_data(string file) {
    ifstream data_file(file.c_str(), std::ifstream::in);

    if (!data_file.is_open()) 
        cout << "Could not open file" << endl;

    string line;
    vector<RedditInfo> reddit_list;
    
    while (getline(data_file, line)) {
        stringstream ss;
        string s[11];
        ss << line;
        
        RedditInfo info;
        
        for(int i = 0; i < 11; i++)
            getline(ss, s[i], ',');

        info.total_votes = stoi(s[0]);
        info.unixtime = stoi(s[1]);
        info.rawtime = s[2];
        info.reddit_id = s[3];
        info.number_of_upvotes = stoi(s[4]);
        info.subreddit = stoi(s[5]);
        info.number_of_downvotes = stoi(s[6]);
        info.localtime = stoi(s[7]);
        info.score = stoi(s[8]);
        info.number_of_comments = stoi(s[9]);
        info.username = s[10];
        
        reddit_list.push_back(info);
    }

    data_file.close();
    
    return reddit_list;
}

void print(vector<RedditInfo>& info) {
    for(vector<RedditInfo>::iterator it = info.begin(); it != info.end(); it++) {
        cout << (*it) << endl;
    }
}