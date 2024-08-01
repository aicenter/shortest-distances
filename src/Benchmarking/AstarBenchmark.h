//
// Author: horakj31 (Jan Horak)
// Created on: 25.07.24
//

#ifndef ASTARBENCHMARK_H
#define ASTARBENCHMARK_H

#include <vector>
#include "../GraphBuilding/Structures/Graph.h"

/**
 * A class that allows us to run Dijkstra's Algorithm on a std::vector of trips. The time of the queries is recorded
// and returned.
 */
class AstarBenchmark {
public:
    /**
     * Runs the basic Dijkstra's Algorithm on a set set of queries (trips).
     * Returns the cumulative time the queries took in seconds. Additionally stores the returned distances
     * into a std::vector so that their correctness can be later verified.
     *
     * @param trips[in] The set of queries (trips) that will be used for the benchmark.
     * @param graph[in] The graph that will be used for the benchmark.
     * @param distances[out] The std::vector that the results of the queries will be saved into. The values in the std::vector
     * can then be used to verify that the returned distances were correct.
     * @return Returns the cumulative time required to answer all the queries in seconds.
     */
    static double benchmark(
            const std::vector < std::pair< unsigned int, unsigned int> > & trips,
            const Graph & graph,
            const std::vector<std::pair<double, double>>& locations,
            std::vector < unsigned int > & distances);

    /**
     * Runs the basic Dijkstra's Algorithm on a set set of queries (trips).
     * Returns the cumulative time the queries took in seconds. Additionally stores the returned distances
     * into a std::vector so that their correctness can be later verified. This variants allows us to query using
     * the IDs in the original graph, because we can provide a mapping from the original IDs to IDs used
     * internally by this application.
     *
     * @param trips[in] The set of queries (trips) that will be used for the benchmark.
     * @param graph[in] The graph that will be used for the benchmark.
     * @param distances[out] The std::vector that the results of the queries will be saved into. The values in the std::vector
     * can then be used to verify that the returned distances were correct.
     * @param mappingFilePath[in] The path to the mapping file.
     * @return Returns the cumulative time required to answer all the queries in seconds.
     */
    static double benchmarkUsingMapping(
            const std::vector < std::pair< long long unsigned int, long long unsigned int> > & trips,
            const Graph & graph,
            const std::vector<std::pair<double, double>>& locations,
            std::vector < unsigned int > & distances,
            std::string mappingFilePath);
};


#endif //ASTARBENCHMARK_H
