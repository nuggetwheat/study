
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <sstream>
#include <vector>

#include "Graph.hpp"

using namespace std;

namespace {
  constexpr std::initializer_list<char> test_nodes{ 'r', 's', 't', 'u', 'v', 'w', 'x', 'y' };
  char test_edges[][2] = {
    {'r', 's'},
    {'r', 'v'},
    {'s', 'w'},
    {'t', 'u'},
    {'u', 'y'},
    {'w', 't'},
    {'w', 'x'},
    {'x', 't'},
    {'x', 'u'},
    {'x', 'y'},
    {(char)0, (char)0}
  };
  char test_bfs_parents[][2] = {
    { 'r', 's' },
    { 's', (char)0 },
    { 't', 'w' },
    { 'u', 't' },
    { 'v', 'r' },
    { 'w', 's' },
    { 'x', 'w' },
    { 'y', 'x' },
    {(char)0, (char)0}    
  };
}

namespace study {

  void test_Graph() {
    Graph<char> g { test_nodes };
    for (size_t i=0; test_edges[i][0]; ++i)
      g.add_edge(test_edges[i][0], test_edges[i][1], EdgeType::UNDIRECTED);

    // BFS
    map<char, char> parents;
    map<char, int> distance;
    bfs(g, 's', parents, distance);
    stringstream ss;
    for (auto &elem : distance)
      ss << elem.first << "=" << elem.second << " ";
    assert(ss.str() == "r=1 s=0 t=2 u=3 v=2 w=1 x=2 y=3 ");
    for (size_t i=0; test_bfs_parents[i][0]; ++i)
      assert(parents[test_bfs_parents[i][0]] == test_bfs_parents[i][1]);
  }

}
