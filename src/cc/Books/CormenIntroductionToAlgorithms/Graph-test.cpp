
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
  constexpr initializer_list<char> test_bfs_nodes {
    'r', 's', 't', 'u', 'v', 'w', 'x', 'y'
      };
  const vector<study::Edge<char>> test_bfs_edges {
    {'r', 's', 1}, {'r', 'v', 1}, {'s', 'w', 1}, {'t', 'u', 1}, {'u', 'y', 1},
    {'w', 't', 1}, {'w', 'x', 1}, {'x', 't', 1}, {'x', 'u', 1}, {'x', 'y', 1}
  };
  const map<char,char> test_bfs_expected_parent {
    { 'r', 's' }, { 's', (char)0 }, { 't', 'w' }, { 'u', 't' }, { 'v', 'r' },
    { 'w', 's' }, { 'x', 'w' }, { 'y', 'x' }
  };
  // DFS
  constexpr initializer_list<char> test_dfs_nodes { 'u', 'v', 'w', 'x', 'y', 'z' };
  const vector<study::Edge<char>> test_dfs_edges {
    {'u', 'v', 1}, {'u', 'x', 1}, {'x', 'v', 1}, {'v', 'y', 1},
    {'y', 'x', 1}, {'w', 'y', 1}, {'w', 'z', 1}, {'z', 'z', 1}
  };
  const map<char,char> test_dfs_expected_parent {
    { 'u', (char)0 }, { 'v', 'u' }, { 'y', 'v' }, { 'x', 'y' },
    { 'w', (char)0 }, { 'z', 'w' }
  };
  // TS
  initializer_list<string> test_ts_nodes{"undershorts", "pants", "belt", "shirt", "tie", "jacket", "socks", "shoes", "watch" };
  const vector<study::Edge<string>> test_ts_edges {
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
  // SCC
  constexpr initializer_list<char> test_scc_nodes{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
  const vector<study::Edge<char>> test_scc_edges {
    {'a', 'b'},
    {'b', 'c'},
    {'b', 'e'},
    {'b', 'f'},
    {'c', 'd'},
    {'c', 'g'},
    {'d', 'c'},
    {'d', 'h'},
    {'e', 'a'},
    {'e', 'f'},
    {'f', 'g'},
    {'g', 'f'},
    {'g', 'h'},
    {'h', 'h'}
  };
  const char *test_scc_groups[] = {
    " a b e",
    " c d",
    " f g",
    " h",
    (const char *)0
  };
  
}


namespace study {

  void test_Graph() {

    // BFS
    {
      Graph<char> g { EdgeType::UNDIRECTED, test_bfs_nodes };
      g.add_edges(test_bfs_edges);

      map<char, char> parent;
      map<char, int> distance;
      bfs(g, 's', parent, distance);
      stringstream ss;
      for (auto &elem : distance)
        ss << elem.first << "=" << elem.second << " ";
      assert(ss.str() == "r=1 s=0 t=2 u=3 v=2 w=1 x=2 y=3 ");
      assert(parent == test_bfs_expected_parent);
    }

    // DFS
    {
      Graph<char> g { EdgeType::DIRECTED, test_dfs_nodes };
      g.add_edges(test_dfs_edges);

      map<char, char> parent;
      map<char, pair<int,int>> time;
      dfs(g, parent, time);
      stringstream ss;
      for (auto &elem : time)
        ss << elem.first << "=" << elem.second.first << "/" << elem.second.second << " ";
      assert(ss.str() == "u=1/8 v=2/7 w=9/12 x=4/5 y=3/6 z=10/11 ");
      assert(parent == test_dfs_expected_parent);
    }

    // TS
    {
      Graph<string> g { EdgeType::DIRECTED, test_ts_nodes };
      g.add_edges(test_ts_edges);
      list<string> order;
      topological_sort(g, order);
      stringstream ss;
      for (auto elem : order)
        ss << " -> " << elem;
      assert(ss.str() == " -> watch -> undershorts -> socks -> shirt -> tie -> pants -> shoes -> belt -> jacket");
    }

    // SCC
    {
      Graph<char> g { EdgeType::DIRECTED, test_scc_nodes };
      g.add_edges(test_scc_edges);
      vector<set<char>> components;
      strongly_connected_components(g, components);
      for (size_t i=0; i<components.size(); ++i) {
        stringstream ss;
        for (const auto elem : components[i])
          ss << " " << elem;
        assert(ss.str() == test_scc_groups[i]);
      }
    }
  }

}
