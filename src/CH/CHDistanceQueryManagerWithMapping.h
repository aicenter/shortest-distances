//
// Author: Xenty (Michal Cvach)
// Created on: 31.07.19
//

#ifndef CONTRACTION_HIERARCHIES_CHDISTANCEQUERYMANAGERWITHMAPPING_H
#define CONTRACTION_HIERARCHIES_CHDISTANCEQUERYMANAGERWITHMAPPING_H


#include "../GraphBuilding/Structures/FlagsGraph.h"
#include "CHDistanceQueryManager.h"
#include <string>
#include <unordered_map>

using namespace std;

// Allows us to answer distance queries using the original indices of the nodes. Internally, nodes are indexed from
// 0 to n-1. Since in the original graph, the nodes indices might be any numbers, this class allows us to load a mapping
// from the original indices to our indices and then answer queries using the original indices. This uses the standard
// CHDistanceQueryManager internally.
//______________________________________________________________________________________________________________________
class CHDistanceQueryManagerWithMapping {
public:
    CHDistanceQueryManagerWithMapping(FlagsGraph & g, string mappingFilepath);
    unsigned int findDistance(const long long unsigned int source, const long long unsigned int target);
private:
    CHDistanceQueryManager qm;
    unordered_map<long long unsigned int, unsigned int> mapping;
};


#endif //CONTRACTION_HIERARCHIES_CHDISTANCEQUERYMANAGERWITHMAPPING_H
