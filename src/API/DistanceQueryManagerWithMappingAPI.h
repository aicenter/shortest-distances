//
// Author: Xenty (Michal Cvach)
// Created on: 9.7.19
//

#ifndef CONTRACTION_HIERARCHIES_DISTANCEQUERYMANAGERWITHMAPPINGAPI_H
#define CONTRACTION_HIERARCHIES_DISTANCEQUERYMANAGERWITHMAPPINGAPI_H


#include "../CH/FloatingPoint/FPointCHDistanceQueryManagerWithMapping.h"
#include <string>

using namespace std;

//______________________________________________________________________________________________________________________
class DistanceQueryManagerWithMappingAPI {
public:
    void initializeCH(string chFile, string mappingFile);
    double distanceQuery(long long unsigned int source, long long unsigned int target);
    void clearStructures();
private:
    FPointCHDistanceQueryManagerWithMapping * qm;
    FPointFlagsGraph * graph;
};


#endif //CONTRACTION_HIERARCHIES_DISTANCEQUERYMANAGERWITHMAPPINGAPI_H