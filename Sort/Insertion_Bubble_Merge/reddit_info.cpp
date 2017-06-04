#include <string>
#include <iostream>
#include <iomanip>

#include "reddit_info.hpp"

using namespace std;

// Prints the Reddit Info to the stream
ostream& operator<<(ostream& os, const RedditInfo& ri) 
{  
    os << setw(5) << ri.total_votes
            << setw(13) << ri.unixtime
            << setw(35) << ri.rawtime
            << setw(10) << ri.reddit_id
            << setw(6) << ri.number_of_upvotes
            << setw(6) << ri.subreddit
            << setw(6) << ri.number_of_downvotes
            << setw(15) << ri.localtime
            << setw(6) << ri.score
            << setw(6) << ri.number_of_comments
            << setw(23) << ri.username;
            
    return os;  
}

bool RedditInfo::operator<=(const RedditInfo &rhs) const {
    return (this->total_votes <= rhs.total_votes);
}

bool RedditInfo::operator<(const RedditInfo &rhs) const {
    return (this->total_votes < rhs.total_votes);
}

void RedditInfo::print_header() {
    cout << setw(5) << "Votes"
        << setw(13) << "Unix Time"
        << setw(35) << "Raw Time"
        << setw(10) << "Id"
        << setw(6) << "# UV"
        << setw(6) << "SR"
        << setw(6) << "# DV"
        << setw(15) << "Local Time"
        << setw(6) << "Score"
        << setw(6) << "Comm."
        << setw(23) << "Username"
        << endl;
}