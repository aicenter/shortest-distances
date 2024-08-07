//
// Author: Xenty (Michal Cvach)
// Created on: 05.10.19
//

#ifndef CONTRACTION_HIERARCHIES_DISTANCEMATRIXBENCHMARK_H
#define CONTRACTION_HIERARCHIES_DISTANCEMATRIXBENCHMARK_H

#include <utility>
#include <vector>
#include "DistanceMatrix/Distance_matrix_travel_time_provider.h"
#include "constants.h"



/**
 * Allows the user to benchmark the Distance Matrix approach with a given set of queries (trips).
 */
class DistanceMatrixBenchmark {
public:
    /**
     * Runs the given set of queries, records the time required for those queries, and puts the results inside the
     * provided std::vector. Returns the time it took to answer all queries in seconds. The distances are not validated
     * inside this function, user is advised to validate that the results are correct somewhere outside this function.
     *
     * @param trips[in] The set of queries (trips) that will be used for the benchmark.
     * @param matrix[in] The distance matrix that will be used for the benchmark.
     * @param distances[out] The std::vector that the results of the queries will be saved into. The values in the std::vector
     * can then be used to verify that the returned distances were correct.
     * @return Returns the cumulative time required to answer all the queries in seconds.
     */
    static double benchmark(
            const std::vector < std::pair< unsigned int, unsigned int> > & trips,
            Distance_matrix_travel_time_provider & matrix,
            std::vector < dist_t > & distances);
};


#endif //CONTRACTION_HIERARCHIES_DISTANCEMATRIXBENCHMARK_H
