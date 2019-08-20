//
// Author: Xenty (Michal Cvach)
// Created on: 20.08.19
//

#ifndef CONTRACTION_HIERARCHIES_PATHCORRECTNESSVALIDATOR_H
#define CONTRACTION_HIERARCHIES_PATHCORRECTNESSVALIDATOR_H


#include "../../GraphBuilding/Structures/IntegerStructures/IntegerFlagsGraphWithUnpackingData.h"
#include "../../GraphBuilding/Structures/IntegerStructures/IntegerGraph.h"

// Auxiliary class used for validating that the paths computed by Contraction Hierarchies also exist in the original
// graph.
//______________________________________________________________________________________________________________________
class PathCorrectnessValidator {
public:
    static void validateOnGivenTrips(vector< pair < unsigned int, unsigned int > > & trips, IntegerFlagsGraphWithUnpackingData & chGraph, IntegerGraph & originalGraph);
};


#endif //CONTRACTION_HIERARCHIES_PATHCORRECTNESSVALIDATOR_H
