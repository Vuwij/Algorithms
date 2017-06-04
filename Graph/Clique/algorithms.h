/* 
 * File:   algorithms.h
 * Author: Dhruv Chawla
 *
 * Created on June 18, 2016, 3:20 PM
 */

#ifndef ALGORITHMS_H
#define	ALGORITHMS_H

#include "Node.h"

#include <set>
#include <unordered_set>
#include <unordered_map>

typedef std::unordered_set<short> group;

extern std::unordered_map<int, Node> NodeMap;

extern group R;
extern group P;
extern group X;
extern group currentMax;

void printGroup(group& G);
void Bron_kerbosch(group P, group R, group X);

#endif	/* ALGORITHMS_H */

