//
// Author: Xenty (Michal Cvach)
// Created on: 25.7.18
//

#include "GraphBuilder/Loader.h"
#include "Dijkstra/BasicDijkstra.h"
#include "Benchmarking/CHBenchmark.h"
#include "Benchmarking/CorectnessValidator.h"
#include "Benchmarking/DijkstraBenchmark.h"
#include "Timer/Timer.h"
#include "TNR/Grid.h"
#include "Utils/MinMaxCoordsFinder.h"
#include "CH/CHPreprocessor.h"
#include "CH/CHQueryManager.h"
#include "CH/CHPathQueryManager.h"


//______________________________________________________________________________________________________________________
void constructCH() {
    Loader graphLoader = Loader("../input/USA-road-t.COL.gr");
    //Loader graphLoader = Loader("input/Rome-road.gr");
    Graph * graph = graphLoader.loadGraph();
    CHPreprocessor::preprocessAndSaveWithUnpackingData("../input/USA.COL.CH_test", *graph);
    //CHPreprocessor::preprocessAndSaveWithUnpackingData("input/Rome_test", *graph);
    delete graph;
}

//______________________________________________________________________________________________________________________
void compareDijkstraWithCHMemoryEconomical() {
    Loader dijkstraGraphLoader = Loader("../input/USA-road-t.COL.gr");
    Graph * dijkstraGraph = dijkstraGraphLoader.loadGraph();
    Loader tripsLoader = Loader("../input/COL1000randomTrips");
    vector< pair < unsigned int, unsigned int > > trips;
    tripsLoader.loadTrips(trips);

    vector<long long unsigned int> dijkstraDistanes(trips.size());
    double dijkstraTime = DijkstraBenchmark::runAndMeasureOutputAndRetval(trips, *dijkstraGraph, dijkstraDistanes);
    delete dijkstraGraph;

    Loader chGraphLoader = Loader("../input/USA.COL.CH_test_graph");
    Graph * chGraph = chGraphLoader.loadGraph();
    Loader ranksLoader = Loader("../input/USA.COL.CH_test_ranks");
    vector<unsigned int> ranks;
    ranksLoader.loadRanks(ranks);

    vector<long long unsigned int> chDistances(trips.size());
    double chTime = CHBenchmark::runAndMeasureOutputAndRetval(trips, *chGraph, ranks, chDistances);
    //for (unsigned int i = 0; i < 20; i++) {
    //    printf("Dijkstra / ch for trip %i: %llu / %llu (trips index from 0)\n", i, dijkstraDistanes[i], chDistances[i]);
    //}
    CorectnessValidator::validateVerbose(dijkstraDistanes, chDistances);
    printf("CH were %lf times faster than Dijkstra!\n", dijkstraTime/chTime);

    delete chGraph;

}

//______________________________________________________________________________________________________________________
void compareDijkstraWithCH() {
    Loader dijkstraGraphLoader = Loader("../input/USA-road-t.COL.gr");
    Graph * dijkstraGraph = dijkstraGraphLoader.loadGraph();
    Loader chGraphLoader = Loader("../input/USA.COL.CH_graph");
    Graph * chGraph = chGraphLoader.loadGraph();
    Loader ranksLoader = Loader("../input/USA.COL.CH_ranks");
    vector<unsigned int> ranks;
    ranksLoader.loadRanks(ranks);

    Loader tripsLoader = Loader("../input/COL1000randomTrips");
    vector< pair < unsigned int, unsigned int > > trips;
    tripsLoader.loadTrips(trips);

    vector<long long unsigned int> dijkstraDistanes(trips.size());
    vector<long long unsigned int> chDistances(trips.size());
    double dijkstraTime = DijkstraBenchmark::runAndMeasureOutputAndRetval(trips, *dijkstraGraph, dijkstraDistanes);
    double chTime = CHBenchmark::runAndMeasureOutputAndRetval(trips, *chGraph, ranks, chDistances);
    //for (unsigned int i = 0; i < 20; i++) {
    //    printf("Dijkstra / ch for trip %i: %llu / %llu (trips index from 0)\n", i, dijkstraDistanes[i], chDistances[i]);
    //}
    CorectnessValidator::validateVerbose(dijkstraDistanes, chDistances);
    printf("CH were %lf times faster than Dijkstra!\n", dijkstraTime/chTime);

    delete dijkstraGraph;
    delete chGraph;

}

//______________________________________________________________________________________________________________________
void getDijkstraPathForTrip() {
    Loader dijkstraGraphLoader = Loader("../input/artifGraph1.gr");
    Graph * dijkstraGraph = dijkstraGraphLoader.loadGraph();

    Loader tripsLoader = Loader("../input/artif1_1000randomTrips");
    vector< pair < unsigned int, unsigned int > > trips;
    tripsLoader.loadTrips(trips);

    unsigned int chosenTrip = 4;
    unsigned long long int distance = BasicDijkstra::runWithPathOutput(trips[chosenTrip].first, trips[chosenTrip].second, *dijkstraGraph);

    delete dijkstraGraph;

}

//______________________________________________________________________________________________________________________
void getCHPathForTrip() {
    Loader chGraphLoader = Loader("../input/artifGraph1.CHv2_graph");
    Graph * chGraph = chGraphLoader.loadGraph();
    Loader ranksLoader = Loader("../input/artifGraph1.CHv2_ranks");
    vector<unsigned int> ranks;
    ranksLoader.loadRanks(ranks);
    Loader unpackingDataLoader = Loader("../input/artifGraph1.CHv2_unpacking");
    map < pair < unsigned int, unsigned int >, unsigned int > unpackingData;
    unpackingDataLoader.loadUnpackingData(unpackingData);

    Loader tripsLoader = Loader("../input/artif1_1000randomTrips");
    vector< pair < unsigned int, unsigned int > > trips;
    tripsLoader.loadTrips(trips);

    unsigned int chosenTrip = 4;

    CHPathQueryManager qm(ranks, unpackingData);
    long long unsigned int distance = qm.findPath(trips.at(chosenTrip).first, trips.at(chosenTrip).second, *chGraph);
    printf("Returned distance: %llu\n", distance);

    delete chGraph;
}

//______________________________________________________________________________________________________________________
void runOneCHQuery() {
    Loader chGraphLoader = Loader("../input/artifGraph1.CH_graph");
    Graph * chGraph = chGraphLoader.loadGraph();
    Loader ranksLoader = Loader("../input/artifGraph1.CH_ranks");
    vector<unsigned int> ranks;
    ranksLoader.loadRanks(ranks);

    Loader tripsLoader = Loader("../input/artif1_1000randomTrips");
    vector< pair < unsigned int, unsigned int > > trips;
    tripsLoader.loadTrips(trips);

    unsigned int chosenTrip = 0;

    CHQueryManager qm(ranks);
    long long unsigned int distance = qm.findDistance(trips.at(chosenTrip).first, trips.at(chosenTrip).second, *chGraph);
    printf("Returned distance: %llu\n", distance);

    delete chGraph;
}

//______________________________________________________________________________________________________________________
int main() {
    //constructCH();
    //compareDijkstraWithCH();
    compareDijkstraWithCHMemoryEconomical();
    //runOneCHQuery();
    //getDijkstraPathForTrip();
    //getCHPathForTrip();

    return 0;
}