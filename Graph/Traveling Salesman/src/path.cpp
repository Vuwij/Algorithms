#include <iomanip>
#include "path.hpp"

void Path::print() {
    cout << this << endl;
}

float Path::get_total_length() const {
    float total_length = 0;
    
    Node* prev = *this->begin();
    for (auto it = this->begin()++; it != this->end(); it++) {
        int id1 = (*it)->id;
        int id2 = prev->id;
        total_length += g->adjacency_matrix[id2][id1];
        prev = *it;
    }
    return total_length;
}

ostream& operator<<(ostream& os, const Path& u) {
    os << "OPTIMAL TOUR LENGTH:  " << setprecision(5) << u.get_total_length() << endl;
    os << "TSP TOUR:" << endl;
    for (auto it = u.begin(); it != u.end(); it++) {
        os << (*it)->id + 1<< endl;
    }
    return os;
}