#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <iostream>

#include "connection.hpp"

#define FLOAT_MAX 3.402823e+38

using namespace std;

// The user is the node of the graph
class Connection;
class User {
    friend class SocialNetwork;
    friend struct UserComp;
private:
    bool visited = false;
    bool isBlack = false;
    float distance = FLOAT_MAX;
    bool influenced = false;
public:
    int id = 0;
    float influence = 0;
    
    User(int id) : id(id) {}
    
    vector<Connection> connections;
    
    void add_connection(User* user, float weight = 0);
    
    bool operator <(const User &rhs);
    bool operator()(User& s1, User& s2);
    bool operator()(User*& s1, User*& s2);
    
    operator int() const { return id; }
    friend ostream& operator<<(ostream& os, const User& u);
};

struct UserComp {
    bool operator()( User*& x, User*& y) const
    {
        return x->distance > y->distance;
    }
};

ostream& operator<<(ostream& os, const User& u);

#endif /* USER_HPP */

