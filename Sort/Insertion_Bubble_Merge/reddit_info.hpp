#ifndef REDDIT_INFO_HPP
#define REDDIT_INFO_HPP

#include <iostream>

using namespace std;

class RedditInfo {
public:
    int total_votes;
    int unixtime;
    string rawtime;
    string reddit_id;
    int number_of_upvotes;
    int subreddit;
    int number_of_downvotes;
    int localtime;
    int score;
    int number_of_comments;
    string username;
    
    // Prints the reddit info
    friend ostream& operator<<(ostream& os, const RedditInfo& info);
    
    bool operator<=(const RedditInfo &rhs) const;
    bool operator<(const RedditInfo &rhs) const;
    
    static void print_header();
};

ostream& operator<<(ostream& os, const RedditInfo& ri);

#endif /* REDDIT_INFO_HPP */

