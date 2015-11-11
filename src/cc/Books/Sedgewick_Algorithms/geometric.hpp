
#ifndef Books_Sedgewick_Algorithms_geometric_hpp
#define Books_Sedgewick_Algorithms_geometric_hpp

#include <cassert>

struct Point {
  int x;
  int y;
};

struct Line {
  Point p1, p2;
};

extern int ccw(Point p0, Point p1, Point p2);

extern bool intersect(Line l1, Line l2);

#define CCW_TEST_COUNT 22

namespace {

  Point ccw_test_points[CCW_TEST_COUNT][3] = {
    { {3, 9}, {11, 1}, {6, 8} },
    { {3, 9}, {11, 1}, {4, 3} },
    { {1, 1}, {2, 2}, {3, 3} },
    { {1, 7}, {2, 7}, {3, 7} },
    { {7, 1}, {7, 2}, {7, 3} },
    { {3, 3}, {2, 2}, {1, 1} },
    { {3, 7}, {2, 7}, {1, 7} },
    { {7, 3}, {7, 2}, {7, 1} },
    { {1, 1}, {3, 3}, {2, 2} },
    { {1, 7}, {3, 7}, {2, 7} },
    { {7, 1}, {7, 3}, {7, 2} },
    { {3, 3}, {1, 1}, {2, 2} },
    { {3, 7}, {1, 7}, {2, 7} },
    { {7, 3}, {7, 1}, {7, 2} },
    { {2, 2}, {1, 1}, {3, 3} },
    { {2, 7}, {1, 7}, {3, 7} },
    { {7, 2}, {7, 1}, {7, 3} },
    { {2, 2}, {3, 3}, {1, 1} },
    { {2, 7}, {3, 7}, {1, 7} },
    { {7, 2}, {7, 3}, {7, 1} },
    { {1, 1}, {3, 3}, {3, 3} },
    { {1, 1}, {3, 3}, {1, 1} }
  };

  int ccw_test_answers[CCW_TEST_COUNT] = {
    1,
    -1,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    0,
    0
  };

  Line ccw_test_lines[] = {
    { {1, 1}, {4, 4} },
    { {1, 4}, {4, 1} },
    { {1, 1}, {2, 1} },
    { {3, 1}, {4, 1} },
    { {1, 1}, {3, 1} },
    { {2, 1}, {4, 1} },
    { {1, 1}, {4, 1} },
    { {2, 1}, {3, 1} },
    { {1, 1}, {3, 3} },
    { {2, 2}, {4, 1} },
    { {1, 1}, {3, 4} },
    { {5, 1}, {5, 3} },
    { {1, 1}, {4, 5} },
    { {3, 3}, {5, 1} }
  };
}

inline void test_ccw() {
  for (int i=0; i<CCW_TEST_COUNT; ++i) {
    assert(ccw(ccw_test_points[i][0], ccw_test_points[i][1], ccw_test_points[i][2]) == ccw_test_answers[i]);
  }
}

inline void test_intersect() {
  assert(intersect(ccw_test_lines[0], ccw_test_lines[1]));
  assert(intersect(ccw_test_lines[1], ccw_test_lines[0]));
  assert(!intersect(ccw_test_lines[2], ccw_test_lines[3]));
  assert(!intersect(ccw_test_lines[3], ccw_test_lines[2]));
  assert(intersect(ccw_test_lines[4], ccw_test_lines[5]));
  assert(intersect(ccw_test_lines[5], ccw_test_lines[4]));
  assert(intersect(ccw_test_lines[6], ccw_test_lines[7]));
  assert(intersect(ccw_test_lines[7], ccw_test_lines[6]));
  assert(intersect(ccw_test_lines[8], ccw_test_lines[9]));
  assert(!intersect(ccw_test_lines[10], ccw_test_lines[11]));
  assert(!intersect(ccw_test_lines[12], ccw_test_lines[13]));
}

#endif // Books_Sedgewick_Algorithms_geometric_hpp
