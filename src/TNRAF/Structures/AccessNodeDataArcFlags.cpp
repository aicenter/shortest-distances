//
// Author: Xenty (Michal Cvach)
// Created on: 30.11.19
//

#include <cstdio>
#include "AccessNodeDataArcFlags.h"

//______________________________________________________________________________________________________________________
AccessNodeDataArcFlags::AccessNodeDataArcFlags(unsigned int a, unsigned int b, unsigned int regionsCnt) : AccessNodeData(a, b), regionFlags(regionsCnt, false) {

}

//______________________________________________________________________________________________________________________
AccessNodeDataArcFlags::AccessNodeDataArcFlags(unsigned int a, unsigned int b, unsigned int regionsCnt, uint32_t regFlags, vector<unsigned int> & powersOf2) : AccessNodeData(a, b), regionFlags(regionsCnt, false) {
    for(unsigned int i = 0; i < regionsCnt; i++) {
        //printf("ArcFlags for region %u\n", i);
        //printf("Reg flags: %u, powersOf2[%u]: %u\n", regFlags, i, powersOf2[i]);
        if (regFlags & powersOf2[i]) {
            regionFlags[i] = true;
        }
    }
}