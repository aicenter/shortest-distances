//
// Author: Xenty (Michal Cvach)
// Created on: 8.7.19
//

#include "../../Timer/Timer.h"
#include "FloatingPointXenGraphLoader.h"
#include <fstream>
#include <iostream>

FloatingPointXenGraphLoader::FloatingPointXenGraphLoader(string inputFile) {
    this->inputFile = inputFile;
}

// Function used to load a graph for the Dijkstra's algorithm. One minor improvement is that we first load the edges
// into an 'IntegerSimpleGraph' instance, which automatically removes multiple (parallel) edges and then construct a 'IntegerGraph'
// from that.
//______________________________________________________________________________________________________________________
FPointGraph * FloatingPointXenGraphLoader::loadGraph() {
    ifstream input;
    input.open(this->inputFile);
    if( ! input.is_open() ) {
        printf("Couldn't open file '%s'!", this->inputFile.c_str());
    }

    printf("Started loading graph!\n");

    Timer graphLoadTimer("FPointGraph loading");
    graphLoadTimer.begin();

    unsigned int nodes, edges;
    parseFirstLine(input, nodes, edges);

    FPointSimpleGraph * graph = new FPointSimpleGraph(nodes);
    parseEdges(input, *graph, edges);

    FPointGraph * retvalGraph = new FPointGraph(*graph);

    delete graph;

    graphLoadTimer.finish();
    graphLoadTimer.printMeasuredTime();

    input.close();

    return retvalGraph;

}

//______________________________________________________________________________________________________________________
FPointUpdateableGraph * FloatingPointXenGraphLoader::loadUpdateableGraph() {
    ifstream input;
    input.open(this->inputFile);
    if( ! input.is_open() ) {
        printf("Couldn't open file '%s'!", this->inputFile.c_str());
    }

    printf("Started loading graph!\n");

    Timer graphLoadTimer("FPointUpdateableGraph loading");
    graphLoadTimer.begin();

    unsigned int nodes, edges;
    parseFirstLine(input, nodes, edges);

    FPointUpdateableGraph * graph = new FPointUpdateableGraph(nodes);
    parseEdges(input, *graph, edges);

    graphLoadTimer.finish();
    graphLoadTimer.printMeasuredTime();

    input.close();

    return graph;
}

//______________________________________________________________________________________________________________________
void FloatingPointXenGraphLoader::loadNodesMapping(unordered_map <long long unsigned int, unsigned int> & mapping) {
    ifstream input;
    input.open(this->inputFile);
    if( ! input.is_open() ) {
        printf("Couldn't open file '%s'!", this->inputFile.c_str());
    }

    printf("Started nodes mapping!\n");

    Timer graphLoadTimer("Mapping loading");
    graphLoadTimer.begin();

    parseNodesMapping(input, mapping);

    graphLoadTimer.finish();
    graphLoadTimer.printMeasuredTime();

    input.close();
}

// This function is used to reinsert all the original edges into the graph after the preprocessing has been finished.
//______________________________________________________________________________________________________________________
void FloatingPointXenGraphLoader::putAllEdgesIntoUpdateableGraph(FPointUpdateableGraph & graph) {
    ifstream input;
    input.open(this->inputFile);
    if( ! input.is_open() ) {
        printf("Couldn't open file '%s'!", this->inputFile.c_str());
    }

    printf("Putting all original edges back into updateable graph!\n");

    Timer graphLoadTimer("Putting back original edges");
    graphLoadTimer.begin();

    unsigned int nodes, edges;
    parseFirstLine(input, nodes, edges);

    parseEdges(input, graph, edges);

    graphLoadTimer.finish();
    graphLoadTimer.printMeasuredTime();

    input.close();

}

//______________________________________________________________________________________________________________________
void FloatingPointXenGraphLoader::parseFirstLine(ifstream & input, unsigned int & nodes, unsigned int & edges) {
    char c1, c2, c3;
    input >> c1 >> c2 >> c3;
    if (c1 != 'X' || c2 != 'G' || c3 != 'F') {
        cout << "The input file is missing the XenGraph header." << endl
        << "Are you sure the input file is in the correct format?" << endl
        << "The loading will proceed but the loaded graph might be corrupted." << endl;
    }

    input >> nodes >> edges;
}

//______________________________________________________________________________________________________________________
void FloatingPointXenGraphLoader::parseEdges(ifstream & input, FPointSimpleGraph & graph, unsigned int edges) {
    unsigned int from, to, oneWayFlag;
    double weight;
    for(unsigned int i = 0; i < edges; i++) {
        input >> from >> to >> weight >> oneWayFlag;
        if (from != to) {
            if (oneWayFlag == 1) {
                graph.addEdge(from, to, weight);
            } else {
                graph.addEdge(from, to, weight);
                graph.addEdge(to, from, weight);
            }
        }
    }
}

//______________________________________________________________________________________________________________________
void FloatingPointXenGraphLoader::parseEdges(ifstream & input, FPointUpdateableGraph & graph, unsigned int edges) {
    unsigned int from, to, oneWayFlag;
    double weight;
    for(unsigned int i = 0; i < edges; i++) {
        input >> from >> to >> weight >> oneWayFlag;
        if (from != to) {
            if (oneWayFlag == 1) {
                graph.addEdge(from, to, weight);
            } else {
                graph.addEdge(from, to, weight);
                graph.addEdge(to, from, weight);
            }
        }
    }
}

//______________________________________________________________________________________________________________________
void FloatingPointXenGraphLoader::parseNodesMapping(ifstream & input, unordered_map <long long unsigned int, unsigned int> & mapping) {
    unsigned int nodes;
    long long unsigned int cur;

    char c1, c2, c3;
    input >> c1 >> c2 >> c3;
    if (c1 != 'X' || c2 != 'I' || c3 != 'D') {
        cout << "The input file is missing the XenGraph indices file header." << endl
             << "Are you sure the input file is in the correct format?" << endl
             << "The loading will proceed but the mapping might be corrupted." << endl;
    }

    input >> nodes;

    for(unsigned int i = 0; i < nodes; i++) {
        input >> cur;
        mapping.insert(make_pair(cur, i));
    }

}