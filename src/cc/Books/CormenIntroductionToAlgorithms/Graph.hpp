
#ifndef Books_CormenIntroductionToAlgorithms_Graph_hpp
#define Books_CormenIntroductionToAlgorithms_Graph_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <utility>

namespace study {

  enum class EdgeType { UNDIRECTED, DIRECTED };

  template <typename T>
  class Graph {
  public:
    Graph(std::initializer_list<T> init);
    void add_edge(const T &u, const T &v, EdgeType et);
    std::list<T> &adj(T u);
    std::set<T> &vertices() { return vertices_; };
    void print();
  private:
    std::set<T> vertices_;
    std::map<T, std::list<T>> alists_;
  };

  template <typename T>
  void bfs(Graph<T> &g, T root, std::map<T, T> &parents, std::map<T, int> &distance);

  template <typename T>
  void dfs(Graph<T> &g, std::map<T, T> &parent, std::map<T, std::pair<int,int>> &time);

  template <typename T>
  void topological_sort(Graph<T> &g, std::list<T> &order);

}

#include "Graph.cpp"

#endif // Books_CormenIntroductionToAlgorithms_Graph_hpp
