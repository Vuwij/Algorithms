/* 
 * File:   Node.cpp
 * Author: Dhruv Chawla
 *
 * Created on June 18, 2016, 3:04 PM
 */

#include "Node.h"

Node::Node() {}

Node::Node(int id_, string type_) {
    id = id_;
    type = type_;
}

void Node::addNeighbours(int Node_id, string connection) {
    neighbours.push_back(std::make_pair(Node_id, connection));
}

void Node::print() {
    cout << "ID: " << id << endl;
    cout << "Neighbours:" << endl;
    for(auto it = neighbours.begin(); it != neighbours.end(); ++it) {
        cout << "Connection: " << (*it).first << " - " << (*it).second << endl;
    }
}