
#ifndef Books_CormenIntroductionToAlgorithms_Graph_hpp
#define Books_CormenIntroductionToAlgorithms_Graph_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>

namespace study {

  enum class EdgeType { UNDIRECTED, DIRECTED };

  template <typename T>
  class Graph {
  public:
    Graph(std::initializer_list<T> init);
    void add_edge(T u, T v, EdgeType et);
    std::list<T> &adj(T u);
    std::set<T> &nodes() { return nodes_; };
    void print();
  private:
    std::set<T> nodes_;
    std::map<T, std::list<T>> alists_;
  };

  template <typename T>
  void bfs(Graph<T> &g, T root, std::map<T, T> &parents, std::map<T, int> &distance);

}

#include "Graph.cpp"

#endif // Books_CormenIntroductionToAlgorithms_Graph_hpp
