
#ifndef Books_AhoHopcroftUllman_DataStructuresAndAlgorithms_Graph_cpp
#define Books_AhoHopcroftUllman_DataStructuresAndAlgorithms_Graph_cpp

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <type_traits>

namespace study {

  template <typename T>
  void greedy_coloring(Graph<T> &g, std::map<T, size_t> &color) {
    size_t next_color = 0;

    std::set<T> uncolored = g.vertices();

    while (!uncolored.empty()) {
      std::set<T> available = uncolored;
      T vertex;
      ++next_color;

      while (!available.empty()) {
        vertex = *available.begin();
        available.erase(available.begin());
        color[vertex] = next_color;
        uncolored.erase(vertex);

        // Remove from available vertices, the ones that point ot vertex
        for (const auto av : available) {
          for (const auto neighbor : g.adj(av)) {
            // A vertex can't be incompatible with itself
            assert(neighbor != av);
            if (neighbor == vertex) {
              available.erase(av);
              break;
            }
          }
        }
      }

    }
  }

}


#endif // Books_AhoHopcroftUllman_DataStructuresAndAlgorithms_Graph_cpp
