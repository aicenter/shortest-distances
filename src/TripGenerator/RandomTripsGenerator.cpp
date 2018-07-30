//
// Author: Xenty (Michal Cvach)
// Created on: 30.7.18
//

#include <cstdio>
#include <cstdlib>

#define NODES_CNT 23947347
#define TRIPS_AMOUNT 100

int main() {
    printf("%u\n", TRIPS_AMOUNT);
    for (unsigned int i = 0; i < TRIPS_AMOUNT; i++) {
        unsigned int source = (rand() % static_cast<int>(NODES_CNT));
        unsigned int target = (rand() % static_cast<int>(NODES_CNT));
        printf("%u %u\n", source, target);
    }

}