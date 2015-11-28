
#ifndef Books_CormenIntroductionToAlgorithms_Graph_cpp
#define Books_CormenIntroductionToAlgorithms_Graph_cpp

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <type_traits>

namespace study {

  enum class VertexColor { WHITE, GRAY, BLACK };
  
  template <typename T>
  void bfs(Graph<T> &g, T root, std::map<T, T> &parent, std::map<T, int> &distance) {
    std::map<T, VertexColor> color;
    for (auto vertex : g.vertices()) {
      parent[vertex] = (char)0;
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
          parent[neighbor] = vertex;
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

  template <typename T, typename DT>
  void relax(T u, T v, std::map<Edge<T>, DT> &weight, std::map<T, T> &parent, std::map<T, DT> &distance) {
    if (distance[u] != std::numeric_limits<DT>::max() &&
        distance[v] > distance[u] + weight[{u,v}]) {
      distance[v] = distance[u] + weight[{u,v}];
      parent[v] = u;
    }
  }

  template <typename T, typename DT>
  void initialize_single_source(Graph<T> &g, T root, std::map<T, T> &parent, std::map<T, DT> &distance) {
    for (auto vertex : g.vertices()) {
      distance[vertex] = std::numeric_limits<DT>::max();
      parent[vertex] = (T)0;
    }
    distance[root] = (DT)0;
  }

  template <typename T, typename DT>
  bool bellman_ford(Graph<T> &g, T root, std::map<Edge<T>, DT> &weight,
                    std::map<T, T> &parent, std::map<T, DT> &distance) {
    initialize_single_source(g, root, parent, distance);
    for (size_t i=0; i<g.vertices().size()-1; ++i)
      for (const auto &edge : g.edges())
        relax(edge.src, edge.dst, weight, parent, distance);
    for (const auto &edge : g.edges())
      if (distance[edge.src] != std::numeric_limits<DT>::max() &&
          distance[edge.dst] > distance[edge.src] + weight[edge])
        return false;
    return true;
  }

  template <typename T, typename DT>
  void dag_shortest_paths(Graph<T> &g, T root, std::map<Edge<T>, DT> &weight,
                          std::map<T, T> &parent, std::map<T, DT> &distance) {
    std::list<T> topo_order;
    topological_sort(g, topo_order);
    initialize_single_source(g, root, parent, distance);
    for (auto vertex : topo_order)
      for (auto neighbor : g.adj(vertex))
        relax(vertex, neighbor, weight, parent, distance);
  }


}


#endif // Books_CormenIntroductionToAlgorithms_Graph_cpp
