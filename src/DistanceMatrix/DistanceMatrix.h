//
// Author: Xenty (Michal Cvach)
// Created on: 05.10.19
//

#ifndef CONTRACTION_HIERARCHIES_DISTANCEMATRIX_H
#define CONTRACTION_HIERARCHIES_DISTANCEMATRIX_H

#include <vector>

using namespace std;

/**
 * Represents a Distance Matrix for a given graph. The Distance Matrix is simply a n*n table ('n' is the number of nodes
 * in the graph) containing precomputed distances between all pairs of nodes. The Distance Matrix is the fastest way
 * to obtain shortest paths, as each query is then only a simple table lookup. The price for this is the memory
 * complexity, which is really high (n^2). This means, that for bigger graphs, we are not able to store the Distance
 * Matrix in memory at once, making it impossible to use it. Here, the Distance Matrix is used for comparison to get an
 * idea of how much slower the other methods are in comparison with the Distance Matrix approach.
 */
class DistanceMatrix {
public:
    /**
     * A simple constructor.
     *
     * @param nodes[in] The number of nodes in the graph (also the number of rows and columns in the matrix).
     */
    explicit DistanceMatrix(const unsigned int nodes);

    /**
     * This is basically a query algorithm. Each query is answered using a single table lookup,
     * as we already have all the shortest distances precomputed in the matrix.
     *
     * @param start[in] The start node for the query.
     * @param goal[in] The goal node for the query.
     * @return Returns the shortest distance from start to goal or 'UINT_MAX' if goal is not reachable from start.
     */
    unsigned int findDistance(const unsigned int start, const unsigned int goal);

    /**
     * Auxiliary function used during the initialization to set the distances.
     *
     * @param source[in] The row of the matrix we want to set the distance for.
     * @param target[in] The column of the table we want to set the distance for.
     * @param distance[in] The value (distance) we wnat to put into the table.
     */
    void setDistance(unsigned int source, unsigned int target, unsigned int distance);

    /**
     * Prints some statistics about the distance matrix. Useful mainly during debugging, might be removed later.
     * Checks how many values in the distance matrix are set to infinity (represented as 'UINT_MAX' in our case).
     * Too many of such values are suspicious and might mean that for example the precision of the graph is too
     * big and the values do not fit into unsigned int anymore.
     */
    void printInfo();

private:
    vector<vector<unsigned int>> distances;
};


#endif //CONTRACTION_HIERARCHIES_DISTANCEMATRIX_H