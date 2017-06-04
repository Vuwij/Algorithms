/* 
 * File:   algorithms.h
 * Author: Dhruv Chawla
 *
 * Created on June 18, 2016, 3:20 PM
 */

#define PRINT_VALUES false

#include "algorithms.h"
#include <iomanip>
/**********************************************************/
// Bron-Kerbosch Algorithm
// R = {}
// P = {v}
// X = {}

//proc BronKerbosch(P,R,X)
// if (P U X) = {} then
//      print set as maximal clique
// end if
// for each vertex C in P \ nbrs(v) do
//      Bron-Kerbosch(P intersect nbrs(v), R U {v}, X intersect(v))
//      P = P \ {v}
//      X = X U {v}
// end for
/**********************************************************/
typedef std::unordered_set<short> group;
int stackDepth = 0;

group groupUnion(group A, group B) {
    group C;
    
    for(auto it = A.begin(); it != A.end(); it++) {
        C.insert(*it);
    }
    
    for(auto it = B.begin(); it != B.end(); it++) {
        C.insert(*it);
    }
    
    return C;
}

group groupIntersect(group A, group B) {
    group C;
    
    for(auto it = A.begin(); it != A.end(); it++) {
        if(B.find(*it) != B.end()) C.insert(*it);
    }
    
    return C;
}

void printGroup(group& G) {
    cout << "{";
    for(auto it = G.begin(); it != G.end(); it++) {
        cout << *it << ",";
    }
    cout << "}";
}

void printStackGroup(group& R, group& P, group& X) {
    cout << setw(stackDepth*3) << " ";
    printGroup(R);
    printGroup(P);
    printGroup(X);
    
    if(P.size() == 0 && X.size() == 0) {
        cout << "--- Maximal Clique ";
        printGroup(R);
        if(R.size() >= currentMax.size()) {
            currentMax = R;
        }
    }
    
    cout << endl;
}

// Bron-Kerbosch Algorithm
// R = {}
// P = {v}
// X = {}

group R;
group P;
group X;
group currentMax;

//proc BronKerbosch(P,R,X)
void Bron_kerbosch(group P, group R, group X) {
    // if (P U X) = {} then
    //  print set as maximal clique
    if(PRINT_VALUES) printStackGroup(R, P, X);
    if(P.size() == 0 && X.size() == 0) {
        return;
    }
    
    // for each vertex v in P do
    while(P.size() > 0) {
        auto it = P.begin();
        
        group nbrs_v, v;
        v.insert(*it);
        for(int i = 0; i < NodeMap[*it].neighbours.size(); i++) {
            nbrs_v.insert(NodeMap[*it].neighbours[i].first);
        }
        
    //  Bron-Kerbosch(P intersect nbrs(v), R U {v}, X intersect nbrs(v))
        stackDepth = stackDepth + 2;
        Bron_kerbosch(
                groupIntersect(P, nbrs_v),
                groupUnion(R, v),
                groupIntersect(X, nbrs_v)
                );
        stackDepth = stackDepth - 2;
    
    //  P = P \ {v}
        P.erase(*it);
        
    //  X = X U {v}
        X = groupUnion(X, v);
        
    // end for        
    }
}

