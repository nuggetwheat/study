
#ifndef Books_CormenIntroductionToAlgorithms_Graph_cpp
#define Books_CormenIntroductionToAlgorithms_Graph_cpp

#include <cassert>
#include <iostream>
#include <queue>
#include <type_traits>

namespace study {

  template <typename T, typename WT>
  Graph<T, WT>::Graph(EdgeType et, std::initializer_list<T> init) : et_(et) {
    for (auto elem : init) {
      vertices_.insert(elem);
      alists_.emplace(elem, std::list<T>());
    }
  }

  template <typename T, typename WT>
  void Graph<T, WT>::add_edge(const T &u, const T &v) {
    assert(vertices_.count(u) && vertices_.count(v));
    alists_[u].push_back(v);
    if (et_ == EdgeType::UNDIRECTED)
      alists_[v].push_back(u);
  }

  template <typename T, typename WT>
  void Graph<T, WT>::add_edge(const Edge<T, WT> &e) {
    assert(vertices_.count(e.src) && vertices_.count(e.dst));
    alists_[e.src].push_back(e.dst);
    if (et_ == EdgeType::UNDIRECTED)
      alists_[e.dst].push_back(e.src);
  }

  template <typename T, typename WT>
  void Graph<T, WT>::add_edges(const std::vector<Edge<T, WT>> &edges) {
    for (const auto &edge : edges)
      add_edge(edge);
  }

  template <typename T, typename WT>
  void Graph<T, WT>::remove_edges() {
    for (auto &elem : alists_)
      elem.second.clear();
  }

  template <typename T, typename WT>
  std::list<T> &Graph<T, WT>::adj(T u) {
    auto iter = alists_.find(u);
    assert(iter != alists_.end());
    return iter->second;
  }

  template <typename T, typename WT>
  std::vector<std::pair<T, T>> Graph<T, WT>::edges() {
    std::vector<std::pair<T, T>> e;
    for (const auto &elem : alists_) {
      for (const auto v : elem.second)
        e.push_back(std::make_pair(elem.first, v));
    }
    return e;
  }

  template <typename T, typename WT>
  void Graph<T, WT>::print() {
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

  template <typename T, typename WT>
  Graph<T, WT> transpose(Graph<T, WT> &g) {
    assert(g.edge_type() == EdgeType::DIRECTED);
    Graph<T, WT> gt(g);
    gt.remove_edges();
    auto edges = g.edges();
    for (const auto &elem : edges)
      gt.add_edge(elem.second, elem.first);
    return gt;
  }


  enum class VertexColor { WHITE, GRAY, BLACK };
  
  template <typename T, typename WT>
  void bfs(Graph<T, WT> &g, T root, std::map<T, T> &parents, std::map<T, int> &distance) {
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

  template <typename T, typename WT>
  void dfs_visit(Graph<T, WT> &g, T u, int &now, std::map<T, VertexColor> &color,
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

  template <typename T, typename WT>
  void dfs_visit_group(Graph<T, WT> &g, T u, std::map<T, VertexColor> &color,
                 std::set<T> &group) {
    color[u] = VertexColor::GRAY;
    group.insert(u);
    for (auto neighbor : g.adj(u)) {
      if (color[neighbor] == VertexColor::WHITE)
        dfs_visit_group(g, neighbor, color, group);
    }
    color[u] = VertexColor::BLACK;
  }

  template <typename T, typename WT>
  void dfs(Graph<T, WT> &g, std::map<T, T> &parent, std::map<T, std::pair<int,int>> &time) {
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

  template <typename T, typename WT>
  void topological_sort(Graph<T, WT> &g, std::list<T> &order) {
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


  template <typename T, typename WT>
  void strongly_connected_components(Graph<T, WT> &g, std::vector<std::set<T>> &components) {
    std::map<T, T> parent;
    std::map<T, std::pair<int,int>> time;
    dfs(g, parent, time);
    auto gp = transpose(g);
    std::vector<std::tuple<int,char>> order;
    order.reserve(gp.vertices().size());
    for (const auto &elem : time)
      order.push_back(std::make_tuple(elem.second.second, elem.first));
    std::sort(order.begin(), order.end(),
              [](const std::tuple<int,char> &lhs, const std::tuple<int,char> &rhs) {
                return std::get<0>(lhs) > std::get<0>(rhs);
              });

    std::map<T, VertexColor> color;
    for (auto vertex : gp.vertices())
      color[vertex] = VertexColor::WHITE;
    components.reserve(color.size());
    std::set<T> group;
    for (const auto &elem : order) {
      if (color[std::get<1>(elem)] == VertexColor::WHITE) {
        group.clear();
        dfs_visit_group(gp, std::get<1>(elem), color, group);
        components.emplace_back(group);
      }
    }
  }



}


#endif // Books_CormenIntroductionToAlgorithms_Graph_cpp
