#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "user.hpp"

// The connection is a single sided edge
class User;
class Connection {
public:
    User* connected_user;
    float weight = 0;
    
    Connection(User* connected_user, float weight = 0);
};

#endif /* SOCIAL_CONNECTION_HPP */

