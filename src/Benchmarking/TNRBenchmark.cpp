/*
 * MIT License
 *
 * Copyright (c) 2024 Czech Technical University in Prague
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

//
// Author: Xenty (Michal Cvach)
// Created on: 06.08.19
//

#include "TNRBenchmark.h"
#include "../Timer/Timer.h"
#include "../TNR/TNRDistanceQueryManager.h"
#include "../TNR/TNRDistanceQueryManagerWithMapping.h"

//______________________________________________________________________________________________________________________
double TNRBenchmark::benchmark(const std::vector < std::pair< unsigned int, unsigned int> > & trips, TransitNodeRoutingGraph<NodeData>& graph, std::vector < unsigned int > & distances) {
    TNRDistanceQueryManager queryManager(graph);

    Timer tnrTimer("Transit Node Routing trips benchmark");
    tnrTimer.begin();

    for(size_t i = 0; i < trips.size(); i++) {
        distances[i] = queryManager.findDistance(trips.at(i).first, trips.at(i).second);
    }

    tnrTimer.finish();
    return tnrTimer.getRealTimeSeconds();
}

//______________________________________________________________________________________________________________________
double TNRBenchmark::benchmarkWithMapping(const std::vector < std::pair< long long unsigned int, long long unsigned int> > & trips, TransitNodeRoutingGraph<NodeData>& graph, std::vector < unsigned int > & distances, std::string mappingFilePath) {
    TNRDistanceQueryManagerWithMapping queryManager(graph, mappingFilePath);

    Timer tnrTimer("Transit Node Routing trips benchmark with mapping");
    tnrTimer.begin();

    for(size_t i = 0; i < trips.size(); i++) {
        distances[i] = queryManager.findDistance(trips.at(i).first, trips.at(i).second);
    }

    tnrTimer.finish();
    return tnrTimer.getRealTimeSeconds();
}
