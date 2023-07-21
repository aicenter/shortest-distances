//
// Author: Xenty (Michal Cvach)
// Created on: 28.10.19
//

#include "PathCorrectnessValidator.h"
#include "../GraphBuilding/Structures/SimpleEdge.h"
#include "../Timer/Timer.h"
#include <iostream>

//______________________________________________________________________________________________________________________
void PathCorrectnessValidator::validateTNRPaths(Graph * originalGraph, TNRPathQueryManager & tnrQueryManager, std::vector< std::pair< unsigned int, unsigned int > > & trips) {
    for(size_t i = 0; i < trips.size(); i++) {
        std::vector<SimpleEdge> path;
        dist_t distance = tnrQueryManager.findPath(trips[i].first, trips[i].second, path);

        if(validatePath(originalGraph, distance, path) == false) {
            std::cout << "Path returned by TNR for trip " << i << " is not valid!" << std::endl;
            return;
        }
    }

    std::cout << "Validated " << trips.size() << " trips. All paths computed by TNR were valid in the original graph." << std::endl;

    Timer pathQueriesTimer = Timer("TNR path queries");
    pathQueriesTimer.begin();

    for(size_t i = 0; i < trips.size(); i++) {
        std::vector<SimpleEdge> path;
        tnrQueryManager.findPath(trips[i].first, trips[i].second, path);
    }

    pathQueriesTimer.finish();
    double time = pathQueriesTimer.getRealTimeSeconds();
    std::cout << "Performed " << trips.size() << " path queries using TNR in " << time << " seconds." << std::endl;
    std::cout << "One query took " << time / ((double) trips.size()) << " seconds." << std::endl;
}

//______________________________________________________________________________________________________________________
void PathCorrectnessValidator::validateCHPaths(Graph * originalGraph, CHPathQueryManager & chQueryManager, std::vector< std::pair< unsigned int, unsigned int > > & trips) {
    for(size_t i = 0; i < trips.size(); i++) {
        std::vector<SimpleEdge> path;
        dist_t distance = chQueryManager.findPath(trips[i].first, trips[i].second, path);

        if(validatePath(originalGraph, distance, path) == false) {
            std::cout << "Path returned by CH for trip " << i << " is not valid!" << std::endl;
            return;
        }
    }

    std::cout << "Validated " << trips.size() << " trips. All paths computed by CH were valid in the original graph." << std::endl;

    Timer pathQueriesTimer = Timer("CH path queries");
    pathQueriesTimer.begin();

    for(size_t i = 0; i < trips.size(); i++) {
        std::vector<SimpleEdge> path;
        chQueryManager.findPath(trips[i].first, trips[i].second, path);
    }

    pathQueriesTimer.finish();
    double time = pathQueriesTimer.getRealTimeSeconds();
    std::cout << "Performed " << trips.size() << " path queries using CH in " << time << " seconds." << std::endl;
    std::cout << "One query took " << ((float) time) / ((float) trips.size()) << " seconds." << std::endl;
}

//______________________________________________________________________________________________________________________
bool PathCorrectnessValidator::validatePath(Graph * originalGraph, const dist_t distance, std::vector<SimpleEdge> & path) {
    if (distance == UINT_MAX && path.empty()) {
        return true;
    }

    dist_t edgesDistance = 0;
    for(size_t i = 0; i < path.size(); i++) {
        dist_t iDistance = checkIfEdgeExists(path[i].from, path[i].to, originalGraph);
        if (iDistance == UINT_MAX) {
            std::cout << "Path returned by TNR contains edge '" << path[i].from << " -> " << path[i].to << "' which does not exist in the original graph." << std::endl;
            return false;
        }
        edgesDistance += iDistance;
    }

    if(edgesDistance != distance) {
        std::cout << "Sum of edge weights of the path returned by TNR does not match the distance returned by TNR." << std::endl;
        std::cout << "Returned distance: " << distance << ", sum of weights: " << edgesDistance << std::endl;
        return false;
    }

    return true;
}

//______________________________________________________________________________________________________________________
unsigned int PathCorrectnessValidator::checkIfEdgeExists(const unsigned int from, const unsigned int to, Graph * originalGraph) {
    const std::vector<std::pair<unsigned int, unsigned int>> & edges = originalGraph->outgoingEdges(from);
    for(size_t i = 0; i < edges.size(); i++) {
        if(edges[i].first == to) {
            return edges[i].second;
        }
    }

    return UINT_MAX;
}
