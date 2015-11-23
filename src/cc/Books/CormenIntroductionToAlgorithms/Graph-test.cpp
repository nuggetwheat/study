
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
    {'r', 's'}, {'r', 'v'}, {'s', 'w'}, {'t', 'u'}, {'u', 'y'},
    {'w', 't'}, {'w', 'x'}, {'x', 't'}, {'x', 'u'}, {'x', 'y'}
  };
  const map<char,char> test_bfs_expected_parent {
    { 'r', 's' }, { 's', (char)0 }, { 't', 'w' }, { 'u', 't' }, { 'v', 'r' },
    { 'w', 's' }, { 'x', 'w' }, { 'y', 'x' }
  };
  // DFS
  constexpr initializer_list<char> test_dfs_nodes { 'u', 'v', 'w', 'x', 'y', 'z' };
  const vector<study::Edge<char>> test_dfs_edges {
    {'u', 'v'}, {'u', 'x'}, {'x', 'v'}, {'v', 'y'},
    {'y', 'x'}, {'w', 'y'}, {'w', 'z'}, {'z', 'z'}
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
  // MST
  constexpr initializer_list<char> test_mst_nodes{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
  const vector<study::Edge<char>> test_mst_edges {
    {'a', 'b'}, {'a', 'h'}, {'b', 'c'}, {'c', 'd'}, {'d', 'e'}, {'e', 'f'},
    {'f', 'c'}, {'f', 'd'}, {'f', 'g'}, {'g', 'h'}, {'g', 'i'}, {'h', 'b'},
    {'h', 'i'}, {'i', 'c'}
  };
  const int test_mst_weight[14] = { 4, 8, 8, 7, 9, 10, 4, 14, 2, 1, 6, 11, 7, 2 };
  // MST-Kruskal
  const vector<study::Edge<char>> test_mst_kruskal_edges_expected {
    {'a', 'b'},
    {'a', 'h'},
    {'c', 'd'},
    {'d', 'e'},
    {'f', 'c'},
    {'f', 'g'},
    {'g', 'h'},
    {'i', 'c'}
  };
  // MST-Prim
  const vector<study::Edge<char>> test_mst_prim_edges_expected {
    {'a', 'b'},
    {'b', 'c'},
    {'c', 'd'},
    {'c', 'f'},
    {'c', 'i'},
    {'d', 'e'},
    {'f', 'g'},
    {'g', 'h'}
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

    // MST-Kruskal
    {
      Graph<char> g { EdgeType::UNDIRECTED, test_mst_nodes };
      Graph<char> mst;
      g.add_edges(test_mst_edges);
      map<Edge<char>, int> weight;
      for (size_t i=0; i<14; ++i) {
        Edge<char> edge = test_mst_edges[i];
        weight[edge] = test_mst_weight[i];
        edge.reverse();
        weight[edge] = test_mst_weight[i];
      }
      mst_kruskal(g, weight, mst);
      auto edges = mst.edges();
      sort(edges.begin(), edges.end());
      assert(edges == test_mst_kruskal_edges_expected);
    }

    // MST-Prim
    {
      Graph<char> g { EdgeType::UNDIRECTED, test_mst_nodes };
      Graph<char> mst;
      g.add_edges(test_mst_edges);
      map<Edge<char>, int> weight;
      for (size_t i=0; i<14; ++i) {
        Edge<char> edge = test_mst_edges[i];
        weight[edge] = test_mst_weight[i];
        edge.reverse();
        weight[edge] = test_mst_weight[i];
      }
      mst_prim(g, 'a', weight, mst);
      auto edges = mst.edges();
      sort(edges.begin(), edges.end());
      assert(edges == test_mst_prim_edges_expected);
    }
  }

}
