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
// Created on: 30.8.18
//

#ifndef TRANSIT_NODE_ROUTING_FLAGSGRAPHWITHUNPACKINGDATA_H
#define TRANSIT_NODE_ROUTING_FLAGSGRAPHWITHUNPACKINGDATA_H

#include <map>
#include "FlagsGraph.h"
#include "QueryEdgeWithUnpackingData.h"

/**
 * Class representing the data structure required for the Contraction Hierarchies query algorithm. This structure
 * contains additional information that can be used to obtain actual shortest paths and not just the shortest distances.
 * The downside of this is that the memory required by this class is bigger than in the case of the normal FlagsGraph.
 */
class FlagsGraphWithUnpackingData {
protected:
    std::vector< std::vector < QueryEdgeWithUnpackingData > > neighbours;
    std::vector< NodeData > nodesData;
    std::vector<unsigned int> forwardPrev;
    std::vector<unsigned int> backwardPrev;
public:
    explicit FlagsGraphWithUnpackingData(unsigned int n);
    unsigned int getMiddleNode(unsigned int source, unsigned int target, bool direction);
    unsigned int getDistance(unsigned int node1, unsigned int node2, bool direction);
    void setForwardPrev(unsigned int x, unsigned int y);
    void setBackwardPrev(unsigned int x, unsigned int y);
    unsigned int getForwardPrev(unsigned int x);
    unsigned int getBackwardPrev(unsigned int x);
    void resetForwardPrev(unsigned int x);
    void resetBackwardPrev(unsigned int x);
    void addEdge(unsigned int from, unsigned int to, unsigned int weight, bool fw, bool bw, unsigned int mNode = UINT_MAX);
    unsigned int nodes() const;
    const std::vector< QueryEdgeWithUnpackingData > & nextNodes(unsigned int x)const;
    NodeData & data(unsigned int node);
    void resetForwardInfo(unsigned int node);
    void resetBackwardInfo(unsigned int node);
    void resetForwardStall(unsigned int node);
    void resetBackwardStall(unsigned int node);
};


#endif //TRANSIT_NODE_ROUTING_FLAGSGRAPHWITHUNPACKINGDATA_H
