/* Insertion Sort
 * 
 */

#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
#include <vector>
#include <valarray>

#include "sort.hpp"
#include "reddit_info.hpp"

using namespace std;

/**
 * Insertion Sort(A)
 * 
 * for j = 2 to A.length
 *     key = A[j]
 *     // Insert A[j] in the sorted sequence A[1..j-1]
 *     i = j - 1
 *     while i > 0 and A[i] > key
 *         A[i + 1] = A[i]
 *         i = i - 1
 *     A[i + 1] = key
 */

typedef vector<RedditInfo>::iterator RedditInfoPtr;

void insertion_sort(vector<RedditInfo> &data) {
    for (vector<RedditInfo>::iterator j = data.begin() + 1; j != data.end(); j++) {
        int key = j->total_votes;
        RedditInfoPtr i = j;
        i--;
        while (i >= data.begin() && i->total_votes > key) {
            iter_swap(i + 1, i);
            i--;
        }
    }
}

int main(int argc, const char* argv[]) {
    // Command Line Arguments
    if (argc != 2) {
        cout << "Usage: sort2 example.csv" << endl;
        return 0;
    }
    
    // Imports the data
    vector<RedditInfo> data = import_data(argv[1]);
    cout << "Unsorted: " << endl;
    RedditInfo::print_header();
    print(data);
    
    // Does Insertion Sort
    insertion_sort(data);
    
    // Prints the data
    cout << "Sorted: " << endl;
    RedditInfo::print_header();
    print(data);
    
    return EXIT_SUCCESS;
}