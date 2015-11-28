
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
  const initializer_list<char> test_bfs_nodes {
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
  const initializer_list<char> test_dfs_nodes { 'u', 'v', 'w', 'x', 'y', 'z' };
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
  const initializer_list<char> test_scc_nodes{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
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
  const initializer_list<char> test_mst_nodes{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
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
  // SSSP
  const initializer_list<char> test_sssp_nodes{ 's', 't', 'x', 'y', 'z' };
  // Bellman-Ford
  const vector<study::Edge<char>> test_bellman_ford_edges {
    {'s', 't'},
    {'s', 'y'},
    {'t', 'x'},
    {'t', 'y'},
    {'t', 'z'},
    {'x', 't'},
    {'y', 'x'},
    {'y', 'z'},
    {'z', 's'},
    {'z', 'x'}
  };
  const int test_bellman_ford_weight[10] = { 6, 7, 5, 8, -4, -2, -3, 9, 2, 7 };
  const vector<char> test_bellman_ford_parent_expected { (char)0, 'x', 'y', 's', 't' };
  const vector<int> test_bellman_ford_distance_expected { 0, 2, 4, 7, -2 };
  // DAG Shortest Paths
  const initializer_list<char> test_dag_sp_nodes{ 'r', 's', 't', 'x', 'y', 'z' };  
  const vector<study::Edge<char>> test_dag_sp_edges {
    {'r', 's'},
    {'r', 't'},
    {'s', 't'},
    {'s', 'x'},
    {'t', 'x'},
    {'t', 'y'},
    {'t', 'z'},
    {'x', 'y'},
    {'x', 'z'},
    {'y', 'z'}
  };
  const int test_dag_sp_weight[10] = { 5, 3, 2, 6, 7, 4, 2, -1, 1, -2 };
  const vector<char> test_dag_sp_parent_expected { (char)0, (char)0, 's', 's', 'x', 'y' };
  const vector<int> test_dag_sp_distance_expected { numeric_limits<int>::max(), 0, 2, 6, 5, 3 };

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

    // Bellman-Ford
    {
      Graph<char> g { EdgeType::DIRECTED, test_sssp_nodes };
      std::map<char, char> parent;
      std::map<char, int> distance;
      g.add_edges(test_bellman_ford_edges);
      map<Edge<char>, int> weight;
      for (size_t i=0; i<10; ++i)
        weight[test_bellman_ford_edges[i]] = test_bellman_ford_weight[i];
      auto valid = bellman_ford(g, 's', weight, parent, distance);
      assert(valid);

      assert (std::search(parent.begin(), parent.end(),
                          test_bellman_ford_parent_expected.begin(),
                          test_bellman_ford_parent_expected.end(),
                          [](std::pair<char, char> lhs, char rhs) {
                            return lhs.second == rhs;
                          }) == parent.begin());

      assert (std::search(distance.begin(), distance.end(),
                          test_bellman_ford_distance_expected.begin(),
                          test_bellman_ford_distance_expected.end(),
                          [](std::pair<char, int> lhs, int rhs) {
                            return lhs.second == rhs;
                          }) == distance.begin());
    }

    // DAG Shortest Paths
    {
      Graph<char> g { EdgeType::DIRECTED, test_dag_sp_nodes };
      std::map<char, char> parent;
      std::map<char, int> distance;
      g.add_edges(test_dag_sp_edges);
      map<Edge<char>, int> weight;
      for (size_t i=0; i<10; ++i)
        weight[test_dag_sp_edges[i]] = test_dag_sp_weight[i];
      dag_shortest_paths(g, 's', weight, parent, distance);

      assert (std::search(parent.begin(), parent.end(),
                          test_dag_sp_parent_expected.begin(),
                          test_dag_sp_parent_expected.end(),
                          [](std::pair<char, char> lhs, char rhs) {
                            return lhs.second == rhs;
                          }) == parent.begin());

      assert (std::search(distance.begin(), distance.end(),
                          test_dag_sp_distance_expected.begin(),
                          test_dag_sp_distance_expected.end(),
                          [](std::pair<char, int> lhs, int rhs) {
                            return lhs.second == rhs;
                          }) == distance.begin());
    }

  }
}
