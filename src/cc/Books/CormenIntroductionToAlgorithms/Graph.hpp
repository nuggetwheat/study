
#ifndef Books_CormenIntroductionToAlgorithms_Graph_hpp
#define Books_CormenIntroductionToAlgorithms_Graph_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>

#include <Common/Graph.hpp>

namespace study {

  template <typename T>
  void bfs(Graph<T> &g, T root, std::map<T, T> &parent, std::map<T, int> &distance);

  template <typename T>
  void dfs(Graph<T> &g, std::map<T, T> &parent, std::map<T, std::pair<int,int>> &time);

  template <typename T>
  void topological_sort(Graph<T> &g, std::list<T> &order);

  template <typename T>
  void strongly_connected_components(Graph<T> &g, std::vector<std::set<T>> &components);

  template <typename T, typename WT>
  void mst_kruskal(const Graph<T> &g, std::map<Edge<T>, WT> &weight, Graph<T> &mst);

  template <typename T, typename WT>
  void mst_prim(const Graph<T> &g, T root, std::map<Edge<T>, WT> &weight, Graph<T> &mst);

  template <typename T, typename DT>
  void relax(T u, T v, std::map<Edge<T>, DT> &weight, std::map<T, T> &parent, std::map<T, DT> &distance);

  template <typename T, typename DT>
  void initialize_single_source(Graph<T> &g, T root, std::map<T, T> &parent, std::map<T, DT> &distance);

  template <typename T, typename DT>
  bool bellman_ford(Graph<T> &g, T root, std::map<Edge<T>, DT> &weight,
                    std::map<T, T> &parent, std::map<T, DT> &distance);

  template <typename T, typename DT>
  void dag_shortest_paths(Graph<T> &g, T root, std::map<Edge<T>, DT> &weight,
                          std::map<T, T> &parent, std::map<T, DT> &distance);

  template <size_t N>
  void display(int M[N][N]);

  template <size_t N>
  void extend_shortest_paths(int L[N][N], int W[N][N], int output[N][N]);

  template <size_t N>
  void slow_all_pairs_shortest_paths(int W[N][N], int output[N][N]);

  template <size_t N>
  void faster_all_pairs_shortest_paths(int W[N][N], int output[N][N]);


}

#include "Graph.cpp"

#endif // Books_CormenIntroductionToAlgorithms_Graph_hpp
