
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
  // BFS
  constexpr std::initializer_list<char> test_bfs_nodes{ 'r', 's', 't', 'u', 'v', 'w', 'x', 'y' };
  char test_bfs_edges[][2] = {
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
  // DFS
  constexpr std::initializer_list<char> test_dfs_nodes{ 'u', 'v', 'w', 'x', 'y', 'z' };
  char test_dfs_edges[][2] = {
    {'u', 'v'},
    {'u', 'x'},
    {'x', 'v'},
    {'v', 'y'},
    {'y', 'x'},
    {'w', 'y'},
    {'w', 'z'},
    {'z', 'z'},
    {(char)0, (char)0}
  };
  char test_dfs_parents[][2] = {
    { 'u', (char)0 },
    { 'v', 'u' },
    { 'y', 'v' },
    { 'x', 'y' },
    { 'w', (char)0 },
    { 'z', 'w' },
    {(char)0, (char)0}    
  };
  // TS
  std::initializer_list<string> test_ts_nodes{"undershorts", "pants", "belt", "shirt", "tie", "jacket", "socks", "shoes", "watch" };
  string test_ts_edges[][2] = {
    {"undershorts", "pants"},
    {"undershorts", "shoes"},
    {"pants", "belt"},
    {"pants", "shoes"},
    {"belt", "jacket"},
    {"shirt", "belt"},
    {"shirt", "tie"},
    {"tie", "jacket"},
    {"socks", "shoes"}
  };
  
}


namespace study {

  void test_Graph() {

    // BFS
    {
      Graph<char> g { test_bfs_nodes };
      for (size_t i=0; test_bfs_edges[i][0]; ++i)
        g.add_edge(test_bfs_edges[i][0], test_bfs_edges[i][1], EdgeType::UNDIRECTED);

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

    // DFS
    {
      Graph<char> g { test_dfs_nodes };
      for (size_t i=0; test_dfs_edges[i][0]; ++i)
        g.add_edge(test_dfs_edges[i][0], test_dfs_edges[i][1], EdgeType::DIRECTED);

      map<char, char> parent;
      map<char, pair<int,int>> time;
      dfs(g, parent, time);
      stringstream ss;
      for (auto &elem : time)
        ss << elem.first << "=" << elem.second.first << "/" << elem.second.second << " ";
      assert(ss.str() == "u=1/8 v=2/7 w=9/12 x=4/5 y=3/6 z=10/11 ");
      for (size_t i=0; test_dfs_parents[i][0]; ++i)
        assert(parent[test_dfs_parents[i][0]] == test_dfs_parents[i][1]);
    }

    // TS
    {
      Graph<string> g { test_ts_nodes };
      for (size_t i=0; i<9; ++i)
        g.add_edge(test_ts_edges[i][0], test_ts_edges[i][1], EdgeType::DIRECTED);
      list<string> order;
      topological_sort(g, order);
      stringstream ss;
      for (auto elem : order)
        ss << " -> " << elem;
      assert(ss.str() == " -> watch -> undershorts -> socks -> shirt -> tie -> pants -> shoes -> belt -> jacket");
    }

  }

}
