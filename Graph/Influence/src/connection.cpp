#include "social_network.hpp"

Connection::Connection(User* connected_user, float weight) {
    this->weight = weight;
    this->connected_user = connected_user;
}