//
// Created by horakj31 on 2024-03-01.
//
#include "gtest/gtest.h"
#include "common.h"
#include "expected_graphs.h"

#include "GraphBuilding/Loaders/DDSGLoader.h"


TEST(ch_test, from_xengraph1) {
    run_preprocessor("-m ch -f xengraph -i functest/01_xengraph.xeng -o from_xengraph1");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_xengraph1.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_01();
    compare_flags_graphs(*loaded, *expected);
}

TEST(ch_test, from_xengraph2) {
    run_preprocessor("-m ch -i functest/02_xengraph.xeng -o from_xengraph2 --precision-loss 100");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_xengraph2.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_02_div100();
    compare_flags_graphs(*loaded, *expected);
}



TEST(ch_test, from_adj1) {
    run_preprocessor("-m ch -f adj -i functest/02_adj.csv -o from_adj1");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_adj1.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_02();
    compare_flags_graphs(*loaded, *expected);
}

TEST(ch_test, from_adj2) {
    run_preprocessor("-m ch --input-format adj -i functest/02_adj.csv -o from_adj2 --precision-loss 100");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_adj2.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_02_div100();
    compare_flags_graphs(*loaded, *expected);
}



TEST(ch_test, from_csv1) {
    run_preprocessor("-m ch -i functest/01_csv -o from_csv1");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_csv1.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_01();
    compare_flags_graphs(*loaded, *expected);
}

TEST(ch_test, from_csv2) {
    run_preprocessor("-m ch --input-format csv -i functest/02_csv -o from_csv2 --precision-loss 100");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_csv2.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_02_div100();
    compare_flags_graphs(*loaded, *expected);
}



TEST(ch_test, from_dimacs1) {
    run_preprocessor("--method ch --input-format dimacs --input-path functest/02_dimacs.gr -o from_dimacs1");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_dimacs1.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_02();
    compare_flags_graphs(*loaded, *expected);
}

TEST(ch_test, from_dimacs2) {
    run_preprocessor("--method ch --input-path functest/02_dimacs.gr --output-path from_dimacs2 --precision-loss 100");
    FlagsGraph<NodeData>* loaded = DDSGLoader("from_dimacs2.ch").loadFlagsGraph();
    FlagsGraph<NodeData>* expected = build_flags_graph_02_div100();
    compare_flags_graphs(*loaded, *expected);
}
