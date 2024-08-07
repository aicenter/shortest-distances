//
// Created by horakj31 on 2024-02-09.
//

#pragma once

#include "GraphBuilding/Structures/FlagsGraph.h"
#include "GraphBuilding/Structures/TransitNodeRoutingGraph.h"
#include "GraphBuilding/Structures/TransitNodeRoutingArcFlagsGraph.h"

void run_preprocessor(const char* args);

void compare_txt_files(const std::string& p1, const std::string& p2);

void compare_flags_graphs(const FlagsGraph& computed, const FlagsGraph& expected);

void compare_tnr_graphs(const TransitNodeRoutingGraph& computed, const TransitNodeRoutingGraph& expected);

void compare_tnraf_graphs(const TransitNodeRoutingArcFlagsGraph& computed, const TransitNodeRoutingArcFlagsGraph& expected);
