/******************************************************************************
 * File:             CsvGraphLoader.cpp
 *
 * Author:           Jan Neumann (neumaja5@fel.cvut.cz)
 * Created:          07/27/20
 *****************************************************************************/

#include "CsvGraphLoader.h"
#include "CLI/ProgressBar.hpp"
#include "GraphBuilding/Structures/Graph.h"
#include "GraphBuilding/Structures/UpdateableGraph.h"
#include <boost/numeric/conversion/cast.hpp>
#include <limits>
#include <stdexcept>
#include <iostream>

using namespace std;

CsvGraphLoader::CsvGraphLoader(string inputFile) : inputFile(inputFile) {
  if(!reader.mmap(inputFile)) {
    throw runtime_error(string("Error reading file ") + this->inputFile +
                        " using mmap.\n");
  }
}

dist_t parse_distance(std::string str, std::string inputFile) {
  float val;
  try {
    val = stof(str);
  }
  catch(std::invalid_argument &e) {
    return std::numeric_limits<dist_t>::max();
  }
  catch(std::out_of_range &e) {
    return std::numeric_limits<dist_t>::max();
  }

  if(isnan(val)) {
    return std::numeric_limits<dist_t>::max();
  }

  if(val < 0) {
    cerr << "Warning: Found a negative value (" << val << ") in '" << inputFile << "'. It will be interpreted as 'no edge'." << endl;
    return std::numeric_limits<dist_t>::max();
  }

  return (dist_t) round(val);
}

unsigned int CsvGraphLoader::nodes() {
  return boost::numeric_cast<unsigned int>(reader.cols());
}

void CsvGraphLoader::loadGraph(BaseGraph &graph) {
    const unsigned int size = nodes();

    if (size != reader.rows())
      throw runtime_error(this->inputFile +
                          " does not contain a square matrix. Found " +
                          to_string(reader.rows()) + " rows and " +
                          to_string(size) + " cols.\n");

    const dist_t max = std::numeric_limits<dist_t>::max();
    ProgressBar progress(size, "Loading CSV file:");

    unsigned int i = 0;
    for (const auto &row : reader) {
      unsigned int j = 0;
      for (const auto &cell : row) {
        string val;
        cell.read_value(val);
        const dist_t dist = parse_distance(val, inputFile);
        if (dist != max)
          graph.addEdge(i, j, dist);
        ++j;
      }
      ++progress;
      ++i;
    }
}
