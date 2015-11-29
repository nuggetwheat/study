
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <random>
#include <sstream>
#include <vector>

#include "Graph.hpp"

using namespace std;

namespace {
  // Greedy coloring
  const initializer_list<string> greedy_coloring_nodes {
    "AB", "AC", "AD", "BA", "BC", "BD", "DA", "DB", "DC", "EA", "EB", "EC", "ED" };
  const vector<study::Edge<string>> greedy_coloring_edges {
    {"AB", "BC"},
    {"AB", "BD"},
    {"AB", "DA"},
    {"AB", "EA"},
    {"AC", "BD"},
    {"AC", "DA"},
    {"AC", "DB"},
    {"AC", "EA"},
    {"AC", "EB"},
    {"AD", "EA"},
    {"AD", "EB"},
    {"AD", "EC"},
    {"BC", "DB"},
    {"BC", "EB"},
    {"BD", "DA"},
    {"BD", "EB"},
    {"BD", "EC"},
    {"DA", "EB"},
    {"DA", "EC"},
    {"DB", "EC"}
  };
  const map<string, size_t> greedy_coloring_expected_colors {
    {"AB", 1},
    {"AC", 1},
    {"AD", 1},
    {"BA", 1},
    {"BC", 2},
    {"BD", 2},
    {"DA", 3},
    {"DB", 3},
    {"DC", 1},
    {"EA", 2},
    {"EB", 4},
    {"EC", 4},
    {"ED", 1}
  };

}


namespace study {

  void test_Graph() {

    // Greedy Coloring
    {
      map<string, size_t> color;
      Graph<string> g { EdgeType::UNDIRECTED, greedy_coloring_nodes };
      g.add_edges(greedy_coloring_edges);
      greedy_coloring(g, color);
      assert(color == greedy_coloring_expected_colors);
    }

  }
}
