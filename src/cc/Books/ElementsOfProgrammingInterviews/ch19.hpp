
#ifndef Books_ElementsOfProgrammingInterviews_ch19_hpp
#define Books_ElementsOfProgrammingInterviews_ch19_hpp

#include <cstdlib>
#include <deque>
#include <ostream>
#include <vector>

namespace study {

  extern size_t CelebrityFinding(const std::vector<std::deque<bool>> &F);

  typedef enum { WHITE, BLACK, GRAY } Color;
  struct Coordinate {
    bool operator==(const Coordinate &that) const {
      return x == that.x && y == that.y;
    };
    size_t x, y;
  };

  inline bool operator<(const Coordinate &lhs, const Coordinate &rhs) {
    if (lhs.x != rhs.x)
      return lhs.x < rhs.x;
    return lhs.y < rhs.y;
  }

  inline std::ostream &operator<<(std::ostream &os, const Coordinate &coord) {
    os << "(" << coord.x << ", " << coord.y << ") ";
    return os;
  }
  
  extern std::vector<Coordinate>
  SearchMaze(std::vector<std::vector<Color>> maze,
             const Coordinate start, const Coordinate finish);

  extern void FlipColor(size_t x, size_t y, std::vector<std::vector<Color>> *A_ptr);

}

#endif // Books_ElementsOfProgrammingInterviews_ch19_hpp
