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
// Created on: 01.12.19
//

#ifndef CONTRACTION_HIERARCHIES_TGAFLOADER_H
#define CONTRACTION_HIERARCHIES_TGAFLOADER_H


#include "TNRGLoader.h"
#include "../Structures/TransitNodeRoutingArcFlagsGraph.h"

/**
 * Class used for loading the Transit Node Routing with Arc Flags data structure. I use a simple binary format for the
 * structure, this function can load those files and initialize TransitNodeRoutingArcFlagsGraph instances from them,
 * which can then be used to answer queries. Since the structures needed by Transit Node Routing with Arc Flags are very
 * similar to the structures needed by Transit Node Routing, some parts of 'TNRGLoader' are reused here.
 */
class TGAFLoader : public TNRGLoader<TransitNodeRoutingArcFlagsGraph> {
public:
    /**
     * A simple constructor.
     *
     * @param inputFile[in] A path towards a file that should be loaded using this loader.
     */
    explicit TGAFLoader(
            std::string inputFile);

    /**
     * Loads the Transit Node Routing with Arc Flags data structures from the file that was given to the loader during
     * its initialization.
     *
     * @return An instance of the 'TransitNodeRoutingArcFlagsGraph' that can be used to answer queries using the
     * Transit Node Routing with Arc Flags query algorithm.
     */
    TransitNodeRoutingArcFlagsGraph* loadTNRAFforDistanceQueries();

protected:
    /**
     * Auxiliary function that parses the header of the file. The header starts with the std::string "TGAF" which is used
     * as a some sort of a magic constant to validate the integrity of the file. After that, four unsigned int numbers
     * should follow, denoting the number of nodes, number of edges, the size of the transit node set,
     * and the number of regions for the Arc Flags.
     *
     * @param input[in] The input stream corresponding to the input file.
     * @param nodes[out] The number of nodes in the graph.
     * @param edges[out] The number of edges in the graph.
     * @param tnodesAmount[out] The size of the transit node set for the Transit Node Routing data-structure.
     * @param regionsCnt[out] The number of regions used for the Arc Flags.
     */
    void parseFirstLine(
            std::ifstream& input,
            unsigned int& nodes,
            unsigned int& edges,
            unsigned int& tnodesAmount,
            unsigned int& regionsCnt);

    /**
     * Parses ranks for all the nodes in the graph.
     *
     * @param input[in] The input stream corresponding to the input file.
     * @param graph[in, out] An instance of the graph the ranks will be loaded into.
     * @param nodes[in] The number of nodes in the graph (we need to load rank for each of the nodes).
     */
    void parseRanks(
            std::ifstream& input,
            TransitNodeRoutingArcFlagsGraph& graph,
            unsigned int nodes);

    /**
     * Parses the region assignments for all the nodes in the graph (necessary for Arc Flags).
     *
     * @param input[in] The input stream corresponding to the input file.
     * @param graph[in, out] An instance of the graph the regions information will be loaded into.
     * @param nodes[in] The number of nodes in the graph (we need to load a region number for each of the nodes).
     */
    void parseRegions(
            std::ifstream& input,
            TransitNodeRoutingArcFlagsGraph& graph,
            unsigned int nodes);

    /**
     * Parses access nodes. This will load access nodes in both directions for all the nodes in the graph along with
     * all their data necessary for the query algorithm.
     *
     * @param input[in] The input stream corresponding to the input file.
     * @param graph[in, out] An instance of the graph the access nodes will be loaded into.
     * @param nodes[in] The number of nodes in the graph (we need access nodes for each node in the graph).
     * @param regionsCnt[in] The number of regions used for the Arc Flags.
     */
    void parseAccessNodes(
            std::ifstream& input,
            TransitNodeRoutingArcFlagsGraph& graph,
            unsigned int nodes,
            unsigned int regionsCnt);
};


#endif //CONTRACTION_HIERARCHIES_TGAFLOADER_H
