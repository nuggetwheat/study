
#ifndef Books_CormenIntroductionToAlgorithms_Graph_cpp
#define Books_CormenIntroductionToAlgorithms_Graph_cpp

#include <cassert>
#include <iostream>
#include <queue>
#include <type_traits>

namespace study {

  template <typename T>
  Graph<T>::Graph(std::initializer_list<T> init) {
    for (auto elem : init) {
      vertices_.insert(elem);
      alists_.emplace(elem, std::list<T>());
    }
  }

  template <typename T>
  void Graph<T>::add_edge(const T &u, const T &v, EdgeType et) {
    assert(vertices_.count(u) && vertices_.count(v));
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

  enum class VertexColor { WHITE, GRAY, BLACK };
  
  template <typename T>
  void bfs(Graph<T> &g, T root, std::map<T, T> &parents, std::map<T, int> &distance) {
    std::map<T, VertexColor> color;
    for (auto vertex : g.vertices()) {
      parents[vertex] = (char)0;
      distance[vertex] = 0;
      color[vertex] = VertexColor::WHITE;
    }
    color[root] = VertexColor::GRAY;
    std::queue<T> needs_visiting;
    needs_visiting.push(root);
    while (!needs_visiting.empty()) {
      T vertex = needs_visiting.front();
      needs_visiting.pop();
      for (auto neighbor : g.adj(vertex)) {
        auto color_iter = color.find(neighbor);
        assert(color_iter != color.end());
        if (color_iter->second == VertexColor::WHITE) {
          color_iter->second = VertexColor::GRAY;
          auto distance_iter = distance.find(neighbor);
          distance_iter->second = distance[vertex] + 1;
          parents[neighbor] = vertex;
          needs_visiting.push(neighbor);
        }
      }
      color[vertex] = VertexColor::BLACK;
    }
  }

  template <typename T>
  void dfs_visit(Graph<T> &g, T u, int &now, std::map<T, VertexColor> &color,
                 std::map<T, T> &parent, std::map<T, std::pair<int,int>> &time) {
    time[u].first = ++now;
    color[u] = VertexColor::GRAY;
    for (auto neighbor : g.adj(u)) {
      if (color[neighbor] == VertexColor::WHITE) {
        parent[neighbor] = u;
        dfs_visit(g, neighbor, now, color, parent, time);
      }
    }
    color[u] = VertexColor::BLACK;
    time[u].second = ++now;
  }

  template <typename T>
  void dfs(Graph<T> &g, std::map<T, T> &parent, std::map<T, std::pair<int,int>> &time) {
    std::map<T, VertexColor> color;
    for (auto vertex : g.vertices()) {
      parent[vertex] = (char)0;
      color[vertex] = VertexColor::WHITE;
    }
    int now = 0;
    for (auto vertex : g.vertices()) {
      if (color[vertex] == VertexColor::WHITE)
        dfs_visit(g, vertex, now, color, parent, time);
    }
  }

  template <typename T>
  void topological_sort(Graph<T> &g, std::list<T> &order) {
    std::map<T, T> parent;
    std::map<T, std::pair<int,int>> time;
    dfs(g, parent, time);
    typedef std::pair<T, std::pair<int,int>> RecType;
    std::vector<RecType> sv;
    sv.reserve(time.size());
    for (auto &elem : time)
      sv.push_back(elem);
    std::sort(sv.begin(), sv.end(),
              [](const RecType &lhs, const RecType &rhs) {
                if (lhs.second.second < rhs.second.second)
                  return true;
                return false;
              });
    for (auto &elem : sv)
      order.push_front(elem.first);
  }



}


#endif // Books_CormenIntroductionToAlgorithms_Graph_cpp
