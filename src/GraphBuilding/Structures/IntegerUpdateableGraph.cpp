//
// Author: Xenty (Michal Cvach)
// Created on: 21.8.18
//

#include <fstream>
#include "IntegerUpdateableGraph.h"

//______________________________________________________________________________________________________________________
IntegerGraph * IntegerUpdateableGraph::createCopy() {
    unsigned int n = nodes();
    IntegerGraph * newInst = new IntegerGraph(n);
    for (unsigned int i = 0; i < n; i++) {
        for (auto iter = followingNodes[i].begin(); iter != followingNodes[i].end(); ++iter) {
            unsigned int target = (*iter).first;
            long long unsigned int weight = (*iter).second.weight;
            newInst->addEdge(i, target, weight);
        }
    }
    return newInst;
}

//______________________________________________________________________________________________________________________
IntegerUpdateableGraph::IntegerUpdateableGraph(unsigned int n) {
    this->followingNodes.resize(n);
    this->previousNodes.resize(n);
    this->ranks.resize(n);
}

//______________________________________________________________________________________________________________________
bool IntegerUpdateableGraph::addEdge(unsigned int from, unsigned int to, long long unsigned int weight) {
    if (followingNodes.at(from).count(to) == 1) {
        if (followingNodes.at(from).at(to).weight > weight) {
            followingNodes.at(from).at(to).weight = weight;
            previousNodes.at(to).at(from) = weight;
            return true;
        }
        return false;
    } else {
        followingNodes.at(from).insert(make_pair(to, IntegerPreprocessingEdgeData(weight, 0, false)));
        previousNodes.at(to).insert(make_pair(from, weight));
        return true;
    }
}

//______________________________________________________________________________________________________________________
bool IntegerUpdateableGraph::addShortcutEdge(unsigned int from, unsigned int to, long long unsigned int weight, unsigned int middlenode) {
    if (followingNodes.at(from).count(to) == 1) {
        if (followingNodes.at(from).at(to).weight > weight) {
            followingNodes.at(from).at(to).weight = weight;
            followingNodes.at(from).at(to).middleNode = middlenode;
            followingNodes.at(from).at(to).isShortcut = true;
            previousNodes.at(to).at(from) = weight;
            return true;
        }
        return false;
    } else {
        followingNodes.at(from).insert(make_pair(to, IntegerPreprocessingEdgeData(weight, middlenode, true)));
        previousNodes.at(to).insert(make_pair(from, weight));
        return true;
    }
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::removeEdge(unsigned int from, unsigned int to) {
    followingNodes.at(from).erase(to);
    previousNodes.at(to).erase(from);
}

//______________________________________________________________________________________________________________________
const unsigned int IntegerUpdateableGraph::getRank(unsigned int nodeID) const {
    return ranks[nodeID];
}

//______________________________________________________________________________________________________________________
const unsigned int IntegerUpdateableGraph::nodes() const {
    return followingNodes.size();
}

//______________________________________________________________________________________________________________________
bool IntegerUpdateableGraph::isShortcut(const unsigned int from, const unsigned int to) {
    return followingNodes[from].at(to).isShortcut;
}

//______________________________________________________________________________________________________________________
const unordered_map<unsigned int, long long unsigned int> & IntegerUpdateableGraph::incomingEdges(const unsigned int x)const {
    return previousNodes.at(x);
}

//______________________________________________________________________________________________________________________
const unordered_map<unsigned int, IntegerPreprocessingEdgeData> & IntegerUpdateableGraph::outgoingEdges(const unsigned int x)const {
    return followingNodes.at(x);
}

//______________________________________________________________________________________________________________________
const unsigned int IntegerUpdateableGraph::degree(unsigned int node)const {
    return followingNodes.at(node).size() + previousNodes.at(node).size();
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::setRank(unsigned int node, unsigned int rank) {
    ranks[node] = rank;
}


// Gets requested amount of highest rank nodes from the Contraction Hierarchy. Those are used in Transit Node Routing
// as Transit Nodes.
//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::getNodesWithHighestRank(vector< unsigned int > & highestNodes, unsigned int requestedAmount) {
    unsigned int curPosition = 0;
    for(unsigned int i = 0; i < requestedAmount; i++) {
        while(ranks[curPosition] <= nodes() - requestedAmount) {
            curPosition++;
        }
        highestNodes[i] = curPosition;
        curPosition++;
    }
}

// Outputs the graph in the format used for the Contraction Hierarchies. This format is briefly described in the
// 'DDSGLoader.h' file.
//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushInDdsgFormat(string filePath) {
    vector < IntegerOutputEdge > edges;
    vector < IntegerOutputShortcutEdge > shortcuts;
    printf("Reordering edges for file writing\n");
    prepareEdgesForFlushing(edges, shortcuts);

    ofstream output;
    output.open ( filePath + ".ch", ios::binary );
    if( ! output.is_open() ) {
        printf("Couldn't open file '%s'!", (filePath + ".ch").c_str());
    }

    printf("Actually flushing the CH graph into the file\n");
    flushHeader(output);
    flushCnts(output, followingNodes.size(), edges.size(), shortcuts.size());
    flushRanks(output);
    flushOriginalEdges(output, edges);
    flushShortcutEdges(output, shortcuts);
    flushTerminator(output);

    output.close();

}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushHeader(ostream & output) {
    char a, b, c, d;
    a = 0x43;
    b = 0x48;
    c = 0x0d;
    d = 0x0a;
    unsigned int version = 1;
    output.write(&a, sizeof (a));
    output.write(&b, sizeof (b));
    output.write(&c, sizeof (c));
    output.write(&d, sizeof (d));
    output.write((char *) &version, sizeof (version));
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushCnts(ostream & output, const unsigned int nodes, const unsigned int edges, const unsigned int shortcuts) {
    output.write((char *) &nodes, sizeof (nodes));
    output.write((char *) &edges, sizeof (edges));
    output.write((char *) &shortcuts, sizeof (shortcuts));
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushRanks(ostream & output) {
    for(unsigned int i = 0; i < ranks.size(); i++) {
        output.write((char *) &ranks[i], sizeof (unsigned int));
    }
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushOriginalEdges(ostream & output, vector < IntegerOutputEdge > & edges) {
    for(unsigned int i = 0; i < edges.size(); i++) {
        output.write((char *) &edges[i].sourceNode, sizeof (unsigned int));
        output.write((char *) &edges[i].targetNode, sizeof (unsigned int));
        output.write((char *) &edges[i].weight, sizeof (unsigned int));
        output.write((char *) &edges[i].flags, sizeof (unsigned int));
    }
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushShortcutEdges(ostream & output, vector < IntegerOutputShortcutEdge > & edges) {
    for(unsigned int i = 0; i < edges.size(); i++) {
        output.write((char *) &edges[i].sourceNode, sizeof (unsigned int));
        output.write((char *) &edges[i].targetNode, sizeof (unsigned int));
        output.write((char *) &edges[i].weight, sizeof (unsigned int));
        output.write((char *) &edges[i].flags, sizeof (unsigned int));
        output.write((char *) &edges[i].middleNode, sizeof (unsigned int));
    }
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::flushTerminator(ostream & output) {
    unsigned int footerNum = 0x12345678;
    output.write((char *) &footerNum, sizeof (footerNum));
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::prepareEdgesForFlushing(vector < IntegerOutputEdge > & edges, vector < IntegerOutputShortcutEdge > & shortcuts) {
   for(unsigned int i = 0; i < followingNodes.size(); i++) {
        for(auto iter = followingNodes[i].begin(); iter != followingNodes[i].end(); ++iter) {
            if (ranks[i] < ranks[(*iter).first]) {
                unsigned int flags = 1;
                if (followingNodes[(*iter).first].count(i) == 1 && followingNodes[(*iter).first].at(i).weight == (*iter).second.weight && followingNodes[(*iter).first].at(i).middleNode == (*iter).second.middleNode) {
                    flags += 2;
                    followingNodes[(*iter).first].erase(i);
                }
                if ((*iter).second.isShortcut) {
                    flags += 4;
                    shortcuts.push_back(IntegerOutputShortcutEdge(i, (*iter).first, (*iter).second.weight, flags, (*iter).second.middleNode));
                } else {
                    edges.push_back(IntegerOutputEdge(i, (*iter).first, (*iter).second.weight, flags));
                }
            } else {
                unsigned int flags = 2;
                if (followingNodes[(*iter).first].count(i) == 1 && followingNodes[(*iter).first].at(i).weight == (*iter).second.weight && followingNodes[(*iter).first].at(i).middleNode == (*iter).second.middleNode) {
                    flags += 1;
                    followingNodes[(*iter).first].erase(i);
                }
                if ((*iter).second.isShortcut) {
                    flags += 4;
                    shortcuts.push_back(IntegerOutputShortcutEdge((*iter).first, i, (*iter).second.weight, flags, (*iter).second.middleNode));
                } else {
                    edges.push_back(IntegerOutputEdge((*iter).first, i, (*iter).second.weight, flags));
                }
            }
        }
    }
}

//______________________________________________________________________________________________________________________
void IntegerUpdateableGraph::prepareEdgesForFlushingWithReinsert(vector < IntegerOutputEdge > & edges, vector < IntegerOutputShortcutEdge > & shortcuts) {
    vector<pair<pair<unsigned int, unsigned int>, IntegerPreprocessingEdgeData>> removedEdges;

    for(unsigned int i = 0; i < followingNodes.size(); i++) {
        for(auto iter = followingNodes[i].begin(); iter != followingNodes[i].end(); ++iter) {
            if (ranks[i] < ranks[(*iter).first]) {
                unsigned int flags = 1;
                if (followingNodes[(*iter).first].count(i) == 1 && followingNodes[(*iter).first].at(i).weight == (*iter).second.weight && followingNodes[(*iter).first].at(i).middleNode == (*iter).second.middleNode) {
                    flags += 2;
                    removedEdges.push_back(make_pair(make_pair((*iter).first, i), IntegerPreprocessingEdgeData(followingNodes[(*iter).first].at(i))));
                    followingNodes[(*iter).first].erase(i);
                }
                if ((*iter).second.isShortcut) {
                    flags += 4;
                    shortcuts.push_back(IntegerOutputShortcutEdge(i, (*iter).first, (*iter).second.weight, flags, (*iter).second.middleNode));
                } else {
                    edges.push_back(IntegerOutputEdge(i, (*iter).first, (*iter).second.weight, flags));
                }
            } else {
                unsigned int flags = 2;
                if (followingNodes[(*iter).first].count(i) == 1 && followingNodes[(*iter).first].at(i).weight == (*iter).second.weight && followingNodes[(*iter).first].at(i).middleNode == (*iter).second.middleNode) {
                    flags += 1;
                    removedEdges.push_back(make_pair(make_pair((*iter).first, i), IntegerPreprocessingEdgeData(followingNodes[(*iter).first].at(i))));
                    followingNodes[(*iter).first].erase(i);
                }
                if ((*iter).second.isShortcut) {
                    flags += 4;
                    shortcuts.push_back(IntegerOutputShortcutEdge((*iter).first, i, (*iter).second.weight, flags, (*iter).second.middleNode));
                } else {
                    edges.push_back(IntegerOutputEdge((*iter).first, i, (*iter).second.weight, flags));
                }
            }
        }
    }

    for(unsigned int i = 0; i < removedEdges.size(); i++) {
        followingNodes[removedEdges[i].first.first].insert(make_pair(removedEdges[i].first.second, IntegerPreprocessingEdgeData(removedEdges[i].second)));
    }
}