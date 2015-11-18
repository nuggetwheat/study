
#ifndef Books_CormenIntroductionToAlgorithms_Graph_cpp
#define Books_CormenIntroductionToAlgorithms_Graph_cpp

#include <cassert>
#include <iostream>
#include <queue>

namespace study {

  template <typename T>
  Graph<T>::Graph(std::initializer_list<T> init) {
    for (auto elem : init)
      nodes_.insert(elem);
  }

  template <typename T>
  void Graph<T>::add_edge(T u, T v, EdgeType et) {
    assert(nodes_.count(u) && nodes_.count(v));
    alists_[u].push_back(v);
    if (et == EdgeType::UNDIRECTED)
      alists_[v].push_back(u);
  }

  template <typename T>
  std::list<T> &Graph<T>::adj(T u) {
    auto iter = alists_.find(u);
    assert(iter != alists_.end());
    return iter->second;
  }

  template <typename T>
  void Graph<T>::print() {
    std::cout << "nodes:";
    for (auto node : nodes_)
      std::cout << " " << node;
    std::cout << "\n";
    for (auto elem : alists_) {
      std::cout << elem.first << " ->";
      for (auto member : elem.second)
        std::cout << " " << member;
      std::cout << std::endl;
    }
  }

  enum class VertexColor { WHITE, GRAY, BLACK };
  
  template <typename T>
  void bfs(Graph<T> &g, T root, std::map<T, T> &parents, std::map<T, int> &distance) {
    std::map<T, VertexColor> color;
    for (auto node : g.nodes()) {
      parents[node] = (char)0;
      distance[node] = 0;
      color[node] = VertexColor::WHITE;
    }
    color[root] = VertexColor::GRAY;
    std::queue<T> needs_visiting;
    needs_visiting.push(root);
    while (!needs_visiting.empty()) {
      T node = needs_visiting.front();
      needs_visiting.pop();
      for (auto neighbor : g.adj(node)) {
        auto color_iter = color.find(neighbor);
        assert(color_iter != color.end());
        if (color_iter->second == VertexColor::WHITE) {
          color_iter->second = VertexColor::GRAY;
          auto distance_iter = distance.find(neighbor);
          distance_iter->second = distance[node] + 1;
          parents[neighbor] = node;
          needs_visiting.push(neighbor);
        }
      }
      color[node] = VertexColor::BLACK;
    }
  }


}


#endif // Books_CormenIntroductionToAlgorithms_Graph_cpp
