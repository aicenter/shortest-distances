//
// Author: Xenty (Michal Cvach)
// Created on: 31.07.19
//

#ifndef CONTRACTION_HIERARCHIES_INTEGERDISTANCEQUERYMANAGERWITHMAPPINGAPI_H
#define CONTRACTION_HIERARCHIES_INTEGERDISTANCEQUERYMANAGERWITHMAPPINGAPI_H


#include "../CH/Integer/IntegerCHDistanceQueryManagerWithMapping.h"
#include <string>

using namespace std;

// This class server as the API which will be used to call the Contraction Hierarchies functionality from Java.
// It should be enough to generate JNI code for this class using SWIG and then use the generated code in Java.
// Using this API, one can load a Contraction Hierarchy (basically prepare all the structures for queries),
// then realize the actual queries, and then clean the structures when they are no longer needed.
// Please note, that if you do not call the 'clearStructures' function manually from Java, memory leaks will occur.
//______________________________________________________________________________________________________________________
class IntegerDistanceQueryManagerWithMappingAPI {
public:
    void initializeCH(string chFile, string mappingFile);
    unsigned int distanceQuery(long long unsigned int source, long long unsigned int target);
    void clearStructures();
private:
    IntegerCHDistanceQueryManagerWithMapping * qm;
    IntegerFlagsGraph * graph;
};


#endif //CONTRACTION_HIERARCHIES_INTEGERDISTANCEQUERYMANAGERWITHMAPPINGAPI_H
