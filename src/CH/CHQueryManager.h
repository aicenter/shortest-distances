//
// Author: Xenty (Michal Cvach)
// Created on: 6.8.18
//

#ifndef TRANSIT_NODE_ROUTING_CHQUERYMANAGER_H
#define TRANSIT_NODE_ROUTING_CHQUERYMANAGER_H

#include <vector>
#include "../GraphBuilder/Graph.h"

using namespace std;

// This class is responsible for the Contraction Hierarchies 'distance' queries - when we only require the 'distance'
// between two points and don't care about the actual path.
//______________________________________________________________________________________________________________________
class CHQueryManager {
public:
    long long unsigned int findDistance(const unsigned int source, const unsigned int target, const Graph & graph);
protected:
};


#endif //TRANSIT_NODE_ROUTING_CHQUERYMANAGER_H
