/* 
 * File:   Node.h
 * Author: Dhruv Chawla
 *
 * Created on June 18, 2016, 2:41 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
    int id = -1;
    string type;
    
    std::vector<std::pair<int, string> > neighbours;
    
    Node();
    Node(int id_, string type_);
    void addNeighbours(int Node_id, string connection);
    void dummy();
    
    void print();
};


#endif	/* NODE_H */

