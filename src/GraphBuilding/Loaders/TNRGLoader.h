//
// Author: Xenty (Michal Cvach)
// Created on: 06.08.19
//

#ifndef CONTRACTION_HIERARCHIES_TNRGLOADER_H
#define CONTRACTION_HIERARCHIES_TNRGLOADER_H

#include <string>
#include "../Structures/IntegerStructures/TransitNodeRoutingGraph.h"
#include "../Structures/IntegerStructures/TransitNodeRoutingGraphForPathQueries.h"

using namespace std;

// Class used for loading the Transit Node Routing data-structure. Currently I use a very simple plain-text file to
// represent the TNR structure. This leads to some really big files with slow processing times though, so I will
// probably change it to some binary format instead later.
//______________________________________________________________________________________________________________________
class TNRGLoader {
private:
    void parseFirstLine(ifstream & input, unsigned int & nodes, unsigned int & edges, unsigned int & tnodesAmount);
    void parseEdgesForDistanceQueries(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int edges);
    void parseEdgesForPathQueries(ifstream & input, TransitNodeRoutingGraphForPathQueries & graph, unsigned int edges);
    void parseRanks(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int nodes);
    void parseTransitNodesMapping(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int tnodesAmount);
    void parseTransitNodesDistanceTable(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int tnodesAmount);
    void parseAccessNodes(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int nodes);
    void parseSearchSpaces(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int nodes);
    void parseRanks(ifstream & input, TransitNodeRoutingGraphForPathQueries & graph, unsigned int nodes);
    void parseTransitNodesMapping(ifstream & input, TransitNodeRoutingGraphForPathQueries & graph, unsigned int tnodesAmount);
    void parseTransitNodesDistanceTable(ifstream & input, TransitNodeRoutingGraphForPathQueries & graph, unsigned int tnodesAmount);
    void parseAccessNodes(ifstream & input, TransitNodeRoutingGraphForPathQueries & graph, unsigned int nodes);
    void parseSearchSpaces(ifstream & input, TransitNodeRoutingGraphForPathQueries & graph, unsigned int nodes);
    void parseLocalityFilter(ifstream & input, TransitNodeRoutingGraph & graph, unsigned int nodes);
    string inputFile;
public:
    TNRGLoader(string inputFile);
    TransitNodeRoutingGraph * loadTNRforDistanceQueries();
    TransitNodeRoutingGraphForPathQueries * loadTNRforPathQueries();
};


#endif //CONTRACTION_HIERARCHIES_TNRGLOADER_H
