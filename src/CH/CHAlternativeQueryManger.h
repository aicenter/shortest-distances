//
// Author: Xenty (Michal Cvach)
// Created on: 27.8.18
//

#ifndef TRANSIT_NODE_ROUTING_CHALTERNATIVEQUERYMANGER_H
#define TRANSIT_NODE_ROUTING_CHALTERNATIVEQUERYMANGER_H

#include <vector>
#include "../GraphBuilder/Graph.h"
#include "CHQueryManager.h"
#include "Structures/QueryPriorityQueue.h"

using namespace std;

class CHAlternativeQueryManager : public CHQueryManager {
public:
    CHAlternativeQueryManager(vector<unsigned int> & x, const Graph & g);
    long long unsigned int findDistance(const unsigned int source, const unsigned int target);
protected:
    vector<unsigned int> & ranks;
    const Graph & graph;
    long long unsigned int upperbound;
    vector<long long unsigned int> forwardDist;
    vector<long long unsigned int> backwardDist;
    vector<unsigned int> forwardChanged;
    vector<unsigned int> backwardChanged;
    //vector<bool> forwardReached;
    //vector<bool> backwardReached;
    vector<bool> forwardSettled;
    vector<bool> backwardSettled;
    QueryPriorityQueue forwardQ;
    QueryPriorityQueue backwardQ;
    void prepareStructuresForNextQuery();
    void relaxForwardEdges(unsigned int curNode, long long unsigned int curLen);
    void relaxBackwardEdges(unsigned int curNode, long long unsigned int curLen);
};


#endif //TRANSIT_NODE_ROUTING_CHALTERNATIVEQUERYMANGER_H
