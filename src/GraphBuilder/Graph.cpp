//
// Author: Xenty (Michal Cvach)
// Created on: 25.7.18
//

#include <cstdio>
#include "Graph.h"

//______________________________________________________________________________________________________________________
Graph::Graph(unsigned int n) {
    this->followingNodes.resize(n);
    this->previousNodes.resize(n);
}

//______________________________________________________________________________________________________________________
void Graph::addEdge(unsigned int from, unsigned int to, long long unsigned int weight) {
    this->followingNodes.at(from).push_back(make_pair(to, weight));
    this->previousNodes.at(to).push_back(make_pair(from, weight));
}

//______________________________________________________________________________________________________________________
const unsigned int Graph::nodes()const {
    return this->followingNodes.size();
}

//______________________________________________________________________________________________________________________
const vector<pair<unsigned int, long long unsigned int>> & Graph::incomingEdges(const unsigned int x)const {
    return this->previousNodes.at(x);
}

//______________________________________________________________________________________________________________________
const vector<pair<unsigned int, long long unsigned int>> & Graph::outgoingEdges(const unsigned int x)const {
    return this->followingNodes.at(x);
}

//______________________________________________________________________________________________________________________
const unsigned int Graph::degree(unsigned int node)const {
    return followingNodes.at(node).size() + previousNodes.at(node).size();
}
