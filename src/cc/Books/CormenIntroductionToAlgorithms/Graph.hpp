
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

namespace study {

  enum class EdgeType { UNDIRECTED, DIRECTED };

  //template <typename T> using Edge = std::pair<T, T>;

  template <typename T>
  struct Edge {
    T src;
    T dst;
    void reverse() { std::swap(src, dst); }
  };

  template <typename T>
  std::ostream &operator<<(std::ostream &os, const Edge<T> &e) {
    return os << e.src << " - " << e.dst;
  }

  template <typename T>
  bool operator<(const Edge<T> &lhs, const Edge<T> &rhs) {
    if (lhs.src == rhs.src)
      return lhs.dst < rhs.dst;
    return lhs.src < rhs.src;
  }

  template <typename T>
  bool operator==(const Edge<T> &lhs, const Edge<T> &rhs) {
    return lhs.src == rhs.src && lhs.dst == rhs.dst;
  }

  template <typename T>
  class Graph {
  public:
    Graph() { }
    Graph(EdgeType et, std::initializer_list<T> init);
    void add_edge(const Edge<T> &e);
    void add_edges(const std::vector<Edge<T>> &edges);
    void clear_edges();
    const std::list<T> &adj(T u) const;
    const std::set<T> &vertices() const { return vertices_; };
    const std::vector<Edge<T>> &edges() const { return edges_; };
    EdgeType edge_type() { return et_; }
    void print();
  private:
    std::set<T> vertices_;
    std::vector<Edge<T>> edges_;
    std::map<T, std::list<T>> alists_;
    EdgeType et_ {};
  };

  template <typename T>
  Graph<T> transpose(Graph<T> &g);

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


}

#include "Graph.cpp"

#endif // Books_CormenIntroductionToAlgorithms_Graph_hpp
