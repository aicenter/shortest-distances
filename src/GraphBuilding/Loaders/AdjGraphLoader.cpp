/******************************************************************************
 * File:             AdjGraphLoader.cpp
 *
 * Author:           Jan Neumann (neumaja5@fel.cvut.cz)
 * Created:          07/27/20
 *****************************************************************************/

#include "AdjGraphLoader.h"
#include "../../CLI/ProgressBar.hpp"
#include "../Structures/Graph.h"
#include <boost/numeric/conversion/cast.hpp>
#include <limits>
#include <stdexcept>
#include <iostream>


AdjGraphLoader::AdjGraphLoader(const std::string& inputFile) : inputFile(inputFile) {
	if (!reader.mmap(inputFile)) {
		throw std::runtime_error(std::string("Error reading file ") + this->inputFile + " using mmap.\n");
	}
}

inline dist_t parse_distance(
	const std::string& str, unsigned int nodeFrom, unsigned int nodeTo, const std::string& inputFile, int scaling_factor
) {
	double val;
	try {
		val = stod(str);
	}
	catch (std::invalid_argument&) {
		std::cerr << "Warning: Found an unexpected value (" << str << ") in '" << inputFile
				  << "'. It will be interpreted as 'no edge' from node " << nodeFrom << " to node " << nodeTo << "."
				  << std::endl;
		return std::numeric_limits<dist_t>::max();
	}
	catch (std::out_of_range&) {
		std::cerr << "Warning: Found an out of range value (" << str << ") in '" << inputFile
				  << "'. It will be interpreted as 'no edge' from node " << nodeFrom << " to node " << nodeTo << "."
				  << std::endl;
		return std::numeric_limits<dist_t>::max();
	}

	if (std::isnan(val)) {
		return std::numeric_limits<dist_t>::max();
	}

	if (val < 0) {
		std::cerr << "Warning: Found a negative value (" << str << ") in '" << inputFile
				  << "'. It will be interpreted as 'no edge' from node " << nodeFrom << " to node " << nodeTo << "."
				  << std::endl;
		return std::numeric_limits<dist_t>::max();
	}

    return (dist_t) std::floor(val / scaling_factor);
}

unsigned int AdjGraphLoader::nodes() {
	return boost::numeric_cast<unsigned int>(reader.cols());
}

void AdjGraphLoader::loadGraph(BaseGraph& graph, int scaling_factor) {
	const unsigned int size = nodes();

	if (size != reader.rows())
		throw std::runtime_error(this->inputFile +
								 " does not contain a square matrix. Found " +
								 std::to_string(reader.rows()) + " rows and " +
								 std::to_string(size) + " cols.\n");

	const dist_t max = std::numeric_limits<dist_t>::max();
	ProgressBar progress(size, "Loading CSV file:");

	unsigned int i = 0;
	//const double multiplier = std::pow(10, scaling_factor);
	for (const auto& row: reader) {
		unsigned int j = 0;
		for (const auto& cell: row) {
			std::string val;
			cell.read_value(val);
			const dist_t dist = parse_distance(val, i, j, inputFile, scaling_factor);
			if (dist != max)
				graph.addEdge(i, j, dist);
			++j;
		}
		++progress;
		++i;
	}
}
