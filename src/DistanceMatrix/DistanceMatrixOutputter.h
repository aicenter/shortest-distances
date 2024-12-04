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
* File:             DistanceMatrixOutputter.h
*
* Author:           Jan Neumann (neumaja5@fel.cvut.cz)  
* Created:          07/28/20 
*****************************************************************************/

#ifndef SHORTEST_PATHS_DISTANCEMATRIXOUTPUTTER_H
#define SHORTEST_PATHS_DISTANCEMATRIXOUTPUTTER_H

#include <string>
#include "Distance_matrix_travel_time_provider.h"

/**
 * Allows to store the distance matrix to disk.
 */
template <class IntType>
class DistanceMatrixOutputter {

public:
 virtual ~DistanceMatrixOutputter() = default;

 /**
 * Store the distance matrix to disk. The distance matrix will be saved into a file
 * specified by the path argument. The appropriate file extension is added automatically.
 *
 * @param dm[in] The distance matrix to store.
 * @param path[in] The desired output file path where the distance matrix should be output.
 */
virtual void store(Distance_matrix_travel_time_provider<IntType>& dm, const std::string &path) = 0;
};


#endif //SHORTEST_PATHS_DISTANCEMATRIXOUTPUTTER_H
