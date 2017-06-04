#include <iomanip>

#include "user.hpp"

void User::add_connection(User* user, float weight) {
    //cout << this->id << " -> " << user->id << " " << weight << endl;
    Connection connection(user, weight);
    connections.push_back(connection);
}

bool User::operator <(const User &rhs) {
    return this->distance < rhs.distance;
}

bool User::operator()(User& s1, User& s2) {
    return s1.distance < s2.distance;
}

bool User::operator()( User*& s1, User*& s2) {
    return s1->distance < s2->distance;
}

ostream& operator<<(ostream& os, const User& u) {
    os << "Node " << u.id << " - " << u.connections.size() << " connections" << endl;
    for(auto it = u.connections.begin(); it != u.connections.end(); it++) {
        os << it->connected_user->id << "\t  " << it->weight << endl;
    } 
    return os;
}