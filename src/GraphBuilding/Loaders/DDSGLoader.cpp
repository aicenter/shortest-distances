//
// Author: Xenty (Michal Cvach)
// Created on: 23.8.18
//

#include <fstream>
#include "DDSGLoader.h"
#include "../../Timer/Timer.h"

//______________________________________________________________________________________________________________________
DDSGLoader::DDSGLoader(std::string inputFile) : inputFile(inputFile) {

}

//______________________________________________________________________________________________________________________
FlagsGraph<NodeData>* DDSGLoader::loadFlagsGraph() {
    std::ifstream input;
    input.open(inputFile, std::ios::binary);

    if ( ! input.is_open() ) {
        printf("Couldn't open file '%s'!", this->inputFile.c_str());
        exit(1);
    }

    if ( verifyHeader(input) == false ) {
        printf("Something was wrong with the header.\nFile should start with 'CH\\r\\n' followed by the");
        printf(" version '1', but it didn't.\n");
        exit(1);
    }

    unsigned int nodes, edges, shortcutEdges;
    loadCnts(input, nodes, edges, shortcutEdges);
    FlagsGraph<NodeData>* graph = new FlagsGraph(nodes);

    loadRanks(input, nodes, *graph);
    loadOriginalEdges(input, edges, *graph);
    loadShortcutEdges(input, shortcutEdges, *graph);

    if ( verifyFooter(input) == false ) {
        printf("The file didn't end the expected way!\nThis file should have ended with an unsigned int");
        printf(" with value '0x12345678', but it didn't.\nThe file could be corrupted, so using it");
        printf(" might provide unexpected and incorrect results.\n");
    }

    return graph;
}

//______________________________________________________________________________________________________________________
FlagsGraphWithUnpackingData * DDSGLoader::loadFlagsGraphWithUnpackingData() {
    std::ifstream input;
    input.open(inputFile, std::ios::binary);

    if ( ! input.is_open() ) {
        printf("Couldn't open file '%s'!", this->inputFile.c_str());
        exit(1);
    }

    if ( verifyHeader(input) == false ) {
        printf("Something was wrong with the header.\nFile should start with 'CH\\r\\n' followed by the");
        printf(" version '1', but it didn't.\n");
        exit(1);
    }

    unsigned int nodes, edges, shortcutEdges;
    loadCnts(input, nodes, edges, shortcutEdges);
    printf("Graph should have %u unpacking pairs\n", shortcutEdges);
    FlagsGraphWithUnpackingData * graph = new FlagsGraphWithUnpackingData(nodes);

    loadRanks(input, nodes, *graph);
    loadOriginalEdges(input, edges, *graph);
    loadShortcutEdgesWithUnpackingData(input, shortcutEdges, *graph);

    if ( verifyFooter(input) == false ) {
        printf("The file didn't end the expected way!\nThis file should have ended with an unsigned int");
        printf(" with value '0x12345678', but it didn't.\nThe file could be corrupted, so using it");
        printf(" might provide unexpected and incorrect results.\n");
    }

    return graph;
}

//______________________________________________________________________________________________________________________
void DDSGLoader::loadRanks(std::ifstream & input, unsigned int nodes, FlagsGraph<NodeData>& graph) {
    for(unsigned int i = 0; i < nodes; i++) {
        unsigned int rank;
        input.read((char*)&rank, sizeof(rank));
        graph.data(i).rank = rank;
    }
}

//______________________________________________________________________________________________________________________
void DDSGLoader::loadRanks(std::ifstream & input, unsigned int nodes, FlagsGraphWithUnpackingData & graph) {
    for(unsigned int i = 0; i < nodes; i++) {
        unsigned int rank;
        input.read((char*)&rank, sizeof(rank));
        graph.data(i).rank = rank;
    }
}

//______________________________________________________________________________________________________________________
void DDSGLoader::loadOriginalEdges(std::ifstream & input, unsigned int edges, FlagsGraph<NodeData>& graph) {
    for(unsigned int i = 0; i < edges; i++) {
        unsigned int from, to, weight, flags;
        input.read((char*)&from, sizeof(from));
        input.read((char*)&to, sizeof(to));
        input.read((char*)&weight, sizeof(weight));
        input.read((char*)&flags, sizeof(flags));

        bool forward = false;
        bool backward = false;
        if((flags & 1) == 1) {
            forward = true;
        }
        if((flags & 2) == 2) {
            backward = true;
        }
        if ( graph.data(from).rank < graph.data(to).rank ) {
            graph.addEdge(from, to, weight, forward, backward);
        } else {
            graph.addEdge(to, from, weight, forward, backward);
        }

    }
}

//______________________________________________________________________________________________________________________
void DDSGLoader::loadOriginalEdges(std::ifstream & input, unsigned int edges, FlagsGraphWithUnpackingData & graph) {
    for(unsigned int i = 0; i < edges; i++) {
        unsigned int from, to, weight, flags;
        input.read((char*)&from, sizeof(from));
        input.read((char*)&to, sizeof(to));
        input.read((char*)&weight, sizeof(weight));
        input.read((char*)&flags, sizeof(flags));

        bool forward = false;
        bool backward = false;
        if((flags & 1) == 1) {
            forward = true;
        }
        if((flags & 2) == 2) {
            backward = true;
        }
        if ( graph.data(from).rank < graph.data(to).rank ) {
            graph.addEdge(from, to, weight, forward, backward);
        } else {
            graph.addEdge(to, from, weight, forward, backward);
        }

    }
}


//______________________________________________________________________________________________________________________
void DDSGLoader::loadShortcutEdges(std::ifstream & input, unsigned int shortcutEdges, FlagsGraph<NodeData>& graph) {
    for(unsigned int i = 0; i < shortcutEdges; i++) {
        unsigned int from, to, weight, flags, middleNode;
        input.read((char*)&from, sizeof(from));
        input.read((char*)&to, sizeof(to));
        input.read((char*)&weight, sizeof(weight));
        input.read((char*)&flags, sizeof(flags));
        input.read((char*)&middleNode, sizeof(middleNode));

        bool forward = false;
        bool backward = false;
        if((flags & 1) == 1) {
            forward = true;
        }
        if((flags & 2) == 2) {
            backward = true;
        }
        if ( graph.data(from).rank < graph.data(to).rank ) {
            graph.addEdge(from, to, weight, forward, backward);
        } else {
            graph.addEdge(to, from, weight, forward, backward);
        }

    }
}

//______________________________________________________________________________________________________________________
void DDSGLoader::loadShortcutEdgesWithUnpackingData(std::ifstream & input, unsigned int shortcutEdges, FlagsGraphWithUnpackingData & graph) {
    for(unsigned int i = 0; i < shortcutEdges; i++) {
        unsigned int from, to, weight, flags, middleNode;
        input.read((char*)&from, sizeof(from));
        input.read((char*)&to, sizeof(to));
        input.read((char*)&weight, sizeof(weight));
        input.read((char*)&flags, sizeof(flags));
        input.read((char*)&middleNode, sizeof(middleNode));

        bool forward = false;
        bool backward = false;
        if((flags & 1) == 1) {
            forward = true;
        }
        if((flags & 2) == 2) {
            backward = true;
        }
        if ( graph.data(from).rank < graph.data(to).rank ) {
            graph.addEdge(from, to, weight, forward, backward, middleNode);
        } else {
            graph.addEdge(to, from, weight, forward, backward, middleNode);
        }

    }
}

//______________________________________________________________________________________________________________________
bool DDSGLoader::verifyHeader(std::ifstream & input) {
    char tmp;
    input.read (&tmp, sizeof(tmp));
    if(tmp != 0x43) {
        return false;
    }
    input.read (&tmp, sizeof(tmp));
    if(tmp != 0x48) {
        return false;
    }
    input.read (&tmp, sizeof(tmp));
    if(tmp != 0x0d) {
        return false;
    }
    input.read (&tmp, sizeof(tmp));
    if(tmp != 0x0a) {
        return false;
    }

    unsigned int version;
    input.read((char*)&version, sizeof(version));
    if (version != 1) {
        return false;
    }

    return true;

}

//______________________________________________________________________________________________________________________
bool DDSGLoader::verifyFooter(std::ifstream & input) {
    unsigned int footerNum;
    input.read((char*)&footerNum, sizeof(footerNum));
    if (footerNum != 0x12345678) {
        return false;
    }
    return true;
}

//______________________________________________________________________________________________________________________
void DDSGLoader::loadCnts(std::ifstream & input, unsigned int & nodes, unsigned int & edges, unsigned int & shortcutEdges) {
    input.read ((char*)&nodes, sizeof(nodes));
    input.read ((char*)&edges, sizeof(edges));
    input.read ((char*)&shortcutEdges, sizeof(shortcutEdges));
}