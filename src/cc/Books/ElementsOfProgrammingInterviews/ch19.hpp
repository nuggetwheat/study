
#ifndef Books_ElementsOfProgrammingInterviews_ch19_hpp
#define Books_ElementsOfProgrammingInterviews_ch19_hpp

#include "reference/ch19.hpp"

#include <cstdlib>
#include <deque>
#include <ostream>
#include <vector>

namespace study {

  extern size_t CelebrityFinding(const std::vector<std::deque<bool>> &F);

  extern std::vector<reference::Coordinate>
  SearchMaze(std::vector<std::vector<reference::Color>> maze,
             const reference::Coordinate start, const reference::Coordinate finish);

  extern void FlipColor(size_t x, size_t y, std::vector<std::vector<reference::Color>> *A_ptr);

}

#endif // Books_ElementsOfProgrammingInterviews_ch19_hpp
