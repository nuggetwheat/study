
#ifndef Books_CormenIntroductionToAlgorithms_Graph_cpp
#define Books_CormenIntroductionToAlgorithms_Graph_cpp

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <type_traits>

namespace study {

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
  void dfs_visit_group(Graph<T> &g, T u, std::map<T, VertexColor> &color,
                 std::set<T> &group) {
    color[u] = VertexColor::GRAY;
    group.insert(u);
    for (auto neighbor : g.adj(u)) {
      if (color[neighbor] == VertexColor::WHITE)
        dfs_visit_group(g, neighbor, color, group);
    }
    color[u] = VertexColor::BLACK;
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


  template <typename T>
  void strongly_connected_components(Graph<T> &g, std::vector<std::set<T>> &components) {
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

  template <typename T, typename WT>
  void mst_kruskal(const Graph<T> &g, std::map<Edge<T>, WT> &weight, Graph<T> &mst) {
    mst = g;
    mst.clear_edges();
    std::map<T, std::shared_ptr<std::set<T>>> group;
    for (auto vertex : g.vertices()) {
      group[vertex] = std::make_shared<std::set<T>>();
      group[vertex]->insert(vertex);
    }
    auto edges = g.edges();
    std::sort(edges.begin(), edges.end(),
              [&weight](const Edge<T> &lhs, const Edge<T> &rhs) {
                if (weight[lhs] == weight[rhs]) {
                  if (lhs.src == rhs.src)
                    return lhs.dst < rhs.dst;
                  return lhs.src < rhs.src;
                }
                return weight[lhs] < weight[rhs];
              });
    for (auto edge : edges) {
      if (group[edge.src]->begin() != group[edge.dst]->begin()) {
        if (*group[edge.src]->begin() < *group[edge.dst]->begin()) {
          group[edge.src]->insert(group[edge.dst]->begin(), group[edge.dst]->end());
          for (auto vertex : *group[edge.dst])
            group[vertex] = group[edge.src];
        }
        else {
          group[edge.dst]->insert(group[edge.src]->begin(), group[edge.src]->end());
          for (auto vertex : *group[edge.src])
            group[vertex] = group[edge.dst];
        }
        assert(group[edge.src].get() == group[edge.dst].get());
        mst.add_edge(edge);
      }
    }
  }

  template <typename T, typename WT>
  void mst_prim(const Graph<T> &g, T root, std::map<Edge<T>, WT> &weight, Graph<T> &mst) {
    mst = g;
    mst.clear_edges();
    typedef struct { T parent; WT weight; } VertexInfo;
    std::map<T, VertexInfo> vinfo;
    auto cmp = [&vinfo](T lhs, T rhs) {
      auto lwt = vinfo[lhs].weight;
      auto rwt = vinfo[rhs].weight;
      if (lwt == rwt)
        return lhs > rhs;
      return lwt > rwt;
    };
    std::vector<T> qheap;
    for (auto vertex : g.vertices()) {
      if (vertex == root)
        vinfo[vertex] = { (T)0, (WT)0 };
      else
        vinfo[vertex] = { (T)0, std::numeric_limits<WT>::max() };
      qheap.push_back(vertex);
    }
    std::make_heap(qheap.begin(), qheap.end(), cmp);
    while (qheap.begin() != qheap.end()) {
      std::pop_heap(qheap.begin(), qheap.end(), cmp);
      auto u = qheap.back();
      {
        auto iter = vinfo.find(u);
        assert(iter != vinfo.end());
        Edge<T> edge = { iter->second.parent, u };
        if (edge.src)
          mst.add_edge(edge);
        vinfo.erase(iter);
      }
      for (auto v : g.adj(u)) {
        auto iter = vinfo.find(v);
        if (iter != vinfo.end() && weight[{u,v}] < iter->second.weight) {
          iter->second.parent = u;
          iter->second.weight = weight[{u,v}];
        }
      }
      qheap.resize(qheap.size()-1);
    }
  }

}


#endif // Books_CormenIntroductionToAlgorithms_Graph_cpp
