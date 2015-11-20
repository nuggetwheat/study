
#ifndef Books_CormenIntroductionToAlgorithms_Graph_hpp
#define Books_CormenIntroductionToAlgorithms_Graph_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace study {

  enum class EdgeType { UNDIRECTED, DIRECTED };

  template <typename T, typename WT = int>
  struct Edge {
    T src;
    T dst;
    WT weight;
  };

  template <typename T, typename WT = int>
  class Graph {
  public:
    Graph(EdgeType et, std::initializer_list<T> init);
    void add_edge(const T &u, const T &v);
    void add_edge(const Edge<T, WT> &e);
    void add_edges(const std::vector<Edge<T, WT>> &edges);
    void remove_edges();
    std::list<T> &adj(T u);
    std::set<T> &vertices() { return vertices_; };
    std::vector<std::pair<T, T>> edges();
    EdgeType edge_type() { return et_; }
    void print();
  private:
    std::set<T> vertices_;
    std::map<T, std::list<T>> alists_;
    EdgeType et_ {};
  };

  template <typename T, typename WT>
  Graph<T, WT> transpose(Graph<T, WT> &g);

  template <typename T, typename WT>
  void bfs(Graph<T, WT> &g, T root, std::map<T, T> &parents, std::map<T, int> &distance);

  template <typename T, typename WT>
  void dfs(Graph<T, WT> &g, std::map<T, T> &parent, std::map<T, std::pair<int,int>> &time);

  template <typename T, typename WT>
  void topological_sort(Graph<T, WT> &g, std::list<T> &order);

  template <typename T, typename WT>
  void strongly_connected_components(Graph<T, WT> &g, std::vector<std::set<T>> &components);

}

#include "Graph.cpp"

#endif // Books_CormenIntroductionToAlgorithms_Graph_hpp
