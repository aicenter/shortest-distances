//
// Author: Xenty (Michal Cvach)
// Created on: 29.8.18
//

#ifndef TRANSIT_NODE_ROUTING_OUTPUTEDGE_H
#define TRANSIT_NODE_ROUTING_OUTPUTEDGE_H

// Simple structure used for outputing edges into the binary .ch format. Each instance is one edge with all it's
// necessary information.
//______________________________________________________________________________________________________________________
class OutputEdge {
public:
    OutputEdge(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
    unsigned int sourceNode;
    unsigned int targetNode;
    unsigned int weight;
    unsigned int flags;
};


#endif //TRANSIT_NODE_ROUTING_OUTPUTEDGE_H
