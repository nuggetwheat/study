
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <random>
#include <sstream>
#include <vector>

#include "ch19.hpp"
#include "reference/ch19.hpp"

using namespace std;
using namespace study;

using reference::Color;
using reference::BLACK;
using reference::WHITE;
using reference::Coordinate;

namespace {

  default_random_engine g_re(42);
  uniform_int_distribution<unsigned int> g_dist;

  void testCelebrityFinding() {
    cout << "[ch19] CelebrityFinding" << endl;
  }

  void testSearchMaze() {
    cout << "[ch19] SearchMaze" << endl;
    vector<vector<Color>> maze;
    maze.push_back( { BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE } );
    maze.push_back( { WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    maze.push_back( { BLACK, WHITE, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK } );
    maze.push_back( { WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, WHITE } );
    maze.push_back( { WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    maze.push_back( { WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, WHITE, BLACK, BLACK, WHITE } );
    maze.push_back( { WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE } );
    maze.push_back( { BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE } );
    maze.push_back( { BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK } );
    maze.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE } );
    initializer_list<Coordinate> expected {
      {9, 0}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {6, 0}, {5, 0}, {4, 0}, {3, 0},
      {3, 1}, {2, 1}, {1, 1}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 5},
      {1, 6}, {1, 7}, {1, 8}, {0, 8}, {0, 9} 
    };
    Coordinate start { 9, 0 };
    Coordinate finish { 0, 9 };
    vector<Coordinate> path = study::SearchMaze(maze, start, finish);
    assert(equal(path.begin(), path.end(), expected.begin()));
  }

#if 0
  void printImage(vector<vector<Color>> &A) {
    for (const auto &row : A) {
      cout << '|';
      for (const auto &pixel : row) {
        if (pixel == BLACK)
          cout << "#|";
        else
          cout << " |";
      }
      cout << endl;
    }
  }
#endif

  void testFlipColor() {
    cout << "[ch19] FlipColor" << endl;
    vector<vector<Color>> A, expected;
    A.push_back( { BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK } );
    A.push_back( { WHITE, WHITE, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK, BLACK } );
    A.push_back( { BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK } );
    A.push_back( { WHITE, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, WHITE } );
    A.push_back( { BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE } );
    A.push_back( { BLACK, WHITE, BLACK, WHITE, WHITE, BLACK, WHITE, BLACK, BLACK, BLACK } );
    A.push_back( { WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK, WHITE, WHITE, BLACK } );
    A.push_back( { BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE } );
    A.push_back( { BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK } );
    A.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE } );

    study::FlipColor(5, 4, &A);
    expected.clear();
    expected.push_back( { BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK } );
    expected.push_back( { WHITE, WHITE, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK, BLACK } );
    expected.push_back( { BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK } );
    expected.push_back( { WHITE, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, WHITE } );
    expected.push_back( { BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE } );
    expected.push_back( { BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK } );
    expected.push_back( { BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK } );
    expected.push_back( { BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, WHITE } );
    expected.push_back( { BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK } );
    expected.push_back( { BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE } );
    assert(A == expected);

    study::FlipColor(3, 6, &A);
    expected.clear();
    expected.push_back( { BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    expected.push_back( { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE } );
    assert(A == expected);
  }

}

namespace study {

  void ch19_test() {
    testCelebrityFinding();
    testSearchMaze();
    testFlipColor();
  }

}


