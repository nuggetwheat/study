
#ifndef Books_AhoHopcroftUllman_DataStructuresAndAlgorithms_Graph_hpp
#define Books_AhoHopcroftUllman_DataStructuresAndAlgorithms_Graph_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>

#include <Common/Graph.hpp>

namespace study {

  template <typename T>
  void greedy_coloring(Graph<T> &g, std::map<T, size_t> &parent);

}

#include "Graph.cpp"

#endif // Books_AhoHopcroftUllman_DataStructuresAndAlgorithms_Graph_hpp
