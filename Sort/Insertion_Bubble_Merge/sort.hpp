#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <string>

#include "reddit_info.hpp"

// Imports the data from the CSV file
vector<RedditInfo> import_data(string file);

// Prints the list of Reddit Information
void print(vector<RedditInfo>& info);

#endif /* SORT_HPP */

