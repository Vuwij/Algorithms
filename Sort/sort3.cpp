/* Bubble Sort
 * 
 */

#include "sort.hpp"
#include "reddit_info.hpp"
#include <iostream>

using namespace std;

/**
 * BubbleSort(A)
 *     for i = 1 to A.length - 1
 *         for j = A.length downto i + 1
 *             if A[j] < A[j-1]
 *                 exchange A[j] with A[j- 1]
 * 
 */
void bubble_sort(vector<RedditInfo> &A) {
    for(vector<RedditInfo>::iterator i = A.begin(); i != A.end() - 1; ++i) {
        for(vector<RedditInfo>::iterator j = A.end()-1; j > A.begin(); --j) {
            if((*j) < (*(j-1))) {
                iter_swap(j, j-1);
            }
        }
    }
}

int main(int argc, const char* argv[]) {
    // Command Line Arguments
    if (argc != 2) {
        cout << "Usage: sort3 example.csv" << endl;
        return 0;
    }
    
    // Imports the data
    vector<RedditInfo> data = import_data(argv[1]);
    cout << "Unsorted: " << endl;
    RedditInfo::print_header();
    print(data);
    
    // Does Insertion Sort
    bubble_sort(data);
    
    // Prints the data
    cout << "Sorted: " << endl;
    RedditInfo::print_header();
    print(data);
    
    return 1;
}