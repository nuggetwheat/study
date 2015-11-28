
#ifndef Common_Graph_hpp
#define Common_Graph_hpp

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
  Graph<T>::Graph(EdgeType et, std::initializer_list<T> init) : et_(et) {
    for (auto elem : init) {
      vertices_.insert(elem);
      alists_.emplace(elem, std::list<T>());
    }
  }

  template <typename T>
  void Graph<T>::add_edge(const Edge<T> &e) {
    assert(vertices_.count(e.src) && vertices_.count(e.dst));
    edges_.push_back(e);
    alists_[e.src].push_back(e.dst);
    if (et_ == EdgeType::UNDIRECTED)
      alists_[e.dst].push_back(e.src);
  }

  template <typename T>
  void Graph<T>::add_edges(const std::vector<Edge<T>> &edges) {
    for (const auto &edge : edges)
      add_edge(edge);
  }

  template <typename T>
  void Graph<T>::clear_edges() {
    for (auto &elem : alists_)
      elem.second.clear();
    edges_.clear();
  }

  template <typename T>
  const std::list<T> &Graph<T>::adj(T u) const {
    auto iter = alists_.find(u);
    assert(iter != alists_.end());
    return iter->second;
  }

  template <typename T>
  void Graph<T>::print() {
    std::cout << "vertices:";
    for (auto vertex : vertices_)
      std::cout << " " << vertex;
    std::cout << "\n";
    for (auto elem : alists_) {
      std::cout << elem.first << " ->";
      for (auto member : elem.second)
        std::cout << " " << member;
      std::cout << std::endl;
    }
  }

  template <typename T>
  Graph<T> transpose(Graph<T> &g) {
    assert(g.edge_type() == EdgeType::DIRECTED);
    Graph<T> gt(g);
    gt.clear_edges();
    for (auto edge : g.edges()) {
      edge.reverse();
      gt.add_edge(edge);
    }
    return gt;
  }

}

#endif // Common_Graph_hpp
