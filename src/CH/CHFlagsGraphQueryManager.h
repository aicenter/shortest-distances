//
// Author: Xenty (Michal Cvach)
// Created on: 28.8.18
//

#ifndef TRANSIT_NODE_ROUTING_CHFLAGSGRAPHQUERYMANAGER_H
#define TRANSIT_NODE_ROUTING_CHFLAGSGRAPHQUERYMANAGER_H


#include <vector>
#include <queue>
#include "../GraphBuilder/FlagsGraph.h"
#include "CHQueryManager.h"
#include "Structures/QueryPriorityQueue.h"

using namespace std;

class CHFlagsGraphQueryManager : public CHQueryManager {
public:
    CHFlagsGraphQueryManager(vector<unsigned int> & x, FlagsGraph & g);
    long long unsigned int findDistance(const unsigned int source, const unsigned int target);
protected:
    void forwardStall(unsigned int stallnode, long long unsigned int stalldistance);
    void backwardStall(unsigned int stallnode, long long unsigned int stalldistance);
    vector<unsigned int> & ranks;
    FlagsGraph & graph;
    long long unsigned int upperbound;
    vector<unsigned int> forwardChanged;
    vector<unsigned int> backwardChanged;
    vector<unsigned int> forwardStallChanged;
    vector<unsigned int> backwardStallChanged;
    void prepareStructuresForNextQuery();
};

#endif //TRANSIT_NODE_ROUTING_CHFLAGSGRAPHQUERYMANAGER_H
