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

/******************************************************************************
* File:             CsvGraphLoader.h
*
* Author:           Jan Horak (horakj31@fel.cvut.cz)
* Created:          07/18/24
*****************************************************************************/

#ifndef SHORTEST_PATHS_CSVGRAPHLOADER_H
#define SHORTEST_PATHS_CSVGRAPHLOADER_H


#include "GraphLoader.h"

#define NOMINMAX // prevents the min and max macro definitions from windows.h, which are introduced in p-ranav-csv2
#include <string>
#include <csv2/reader.hpp>

typedef csv2::Reader<csv2::delimiter<'\t'>, csv2::quote_character<'"'>,
                     csv2::first_row_is_header<true>,
                     csv2::trim_policy::trim_characters<' ', '\t', '\r', '\n'>>
    DefaultCSVReader;

class CsvGraphLoader : public GraphLoader {
private:
    DefaultCSVReader nodeReader;
    DefaultCSVReader edgeReader;
    std::string inputPath;
public:
    explicit CsvGraphLoader(const std::string& inputPath);

    using GraphLoader::loadGraph;

    void loadGraph(BaseGraph &graph, int scaling_factor) override;

    unsigned int nodes() override;

    ~CsvGraphLoader() override = default;

    void loadLocations(std::vector<std::pair<double, double>> &locations);
};


#endif //SHORTEST_PATHS_CSVGRAPHLOADER_H
