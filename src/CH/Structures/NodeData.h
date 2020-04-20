//
// Author: Xenty (Michal Cvach)
// Created on: 29.8.18
//

#ifndef TRANSIT_NODE_ROUTING_NODEDATA_H
#define TRANSIT_NODE_ROUTING_NODEDATA_H

/**
 * A simple structure encapsulating all the important information about a node for the Contraction Hierarchies
 * query algorithm.
 */
class NodeData {
public:
    /**
     * A simple constructor that initializes the instance with default values.
     */
    NodeData();

    unsigned int forwardDist;
    unsigned int backwardDist;
    unsigned int rank;
    bool forwardReached;
    bool backwardReached;
    bool forwardSettled;
    bool backwardSettled;
    bool forwardStalled;
    bool backwardStalled;
};


#endif //TRANSIT_NODE_ROUTING_NODEDATA_H