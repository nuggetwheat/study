
#include "ch19.hpp"
#include "reference/ch19.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

extern "C" {
#include <math.h>
}

#include <Common/Graph.hpp>

namespace study {

  size_t CelebrityFinding(const std::vector<std::deque<bool>> &F) {
    return reference::CelebrityFinding(F);
  }

  std::vector<reference::Coordinate>
  SearchMaze(std::vector<std::vector<reference::Color>> maze,
             const reference::Coordinate start, const reference::Coordinate finish) {
    return reference::SearchMaze(maze, start, finish);
  }

  void FlipColor(size_t x, size_t y, std::vector<std::vector<reference::Color>> *A_ptr) {
    reference::FlipColor(x, y, A_ptr);
  }

}
