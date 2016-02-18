
#include "ch19.hpp"

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

using study::Graph;
using study::EdgeType;

namespace reference {

  size_t CelebrityFinding(const std::vector<std::deque<bool>> &F) {
    size_t i = 0, j = 1;
    while (j < F.size()) {
      if (F[i][j])
        i = j++;
      else
        ++j;
    }
    return i;
  }

  bool SearchDown(Graph<Coordinate> &g, Coordinate vertex,
                  Coordinate finish,
                  std::map<Coordinate, int> &color,
                  std::stack<Coordinate> &pstack) {
    //std::cout << vertex << std::endl;
    if (vertex == finish) {
      pstack.push(vertex);
      return false;
    }
    color[vertex] = GRAY;
    for (const auto &neighbor : g.adj(vertex)) {
      if (color[neighbor] == WHITE) {
        if (!SearchDown(g, neighbor, finish, color, pstack)) {
          pstack.push(vertex);
          return false;
        }
      }
    }
    color[vertex] = BLACK;
    return true;
  }

  std::vector<Coordinate>
  SearchMaze(std::vector<std::vector<Color>> maze,
             const Coordinate start, const Coordinate finish) {
    std::stack<Coordinate> pstack;
    std::vector<Coordinate> vertices;
    std::map<Coordinate, int> color;

    for (size_t i=0; i<maze.size(); ++i)
      for (size_t j=0; j<maze[i].size(); ++j) {
        vertices.push_back( {i, j} );
        color[{i, j}] = WHITE;
      }

    Graph<Coordinate> g(EdgeType::UNDIRECTED, vertices);

    // Build graph
    for (size_t i=0; i<maze.size(); ++i) {
      for (size_t j=0; j<maze[i].size(); ++j) {
        if (j < maze[i].size()-1 && maze[i][j] == WHITE && maze[i][j+1] == WHITE)
          g.add_edge({{i, j}, {i, j+1}});
        if (i < maze.size()-1 && maze[i][j] == WHITE && maze[i+1][j] == WHITE)
          g.add_edge({{i, j}, {i+1, j}});
      }
    }

#if 0
    std::cout << "adjacent(start) = ";
    for (const auto &neighbor : g.adj(start))
      std::cout << neighbor;
    std::cout << std::endl;

    std::cout << "adjacent(finish) = ";
    for (const auto &neighbor : g.adj(finish))
      std::cout << neighbor;
    std::cout << std::endl;
#endif

    if (start == finish)
      pstack.push(start);
    else {
      for (const auto &neighbor : g.adj(start)) {
        if (color[neighbor] == WHITE) {
          if (!SearchDown(g, neighbor, finish, color, pstack)) {
            pstack.push(start);
            break;
          }
        }
      }
    }

    std::vector<Coordinate> path;
    path.reserve(pstack.size());
    while (!pstack.empty()) {
      path.push_back(pstack.top());
      pstack.pop();
    }

    return path;
  }

  void FlipColor(size_t x, size_t y, std::vector<std::vector<Color>> *A_ptr) {
    std::vector<std::vector<Color>> &A = *A_ptr;
    std::queue<Coordinate> tbd;
    Color old_color = A[x][y];
    Color new_color = (old_color == WHITE) ? BLACK : WHITE;
    tbd.push({x, y});
    while (!tbd.empty()) {
      Coordinate &coord = tbd.front();

      assert(coord.x < A.size() && coord.y < A[0].size());

      // Flip color
      A[coord.x][coord.y] = new_color;

      if (coord.x > 0 && A[coord.x-1][coord.y] == old_color)
        tbd.push({coord.x-1, coord.y});
      if (coord.y < A[0].size()-1 && A[coord.x][coord.y+1] == old_color)
        tbd.push({coord.x, coord.y+1});
      if (coord.x < A.size()-1 && A[coord.x+1][coord.y] == old_color)
        tbd.push({coord.x+1, coord.y});
      if (coord.y > 0 && A[coord.x][coord.y-1] == old_color)
        tbd.push({coord.x, coord.y-1});
      tbd.pop();
    }
  }

}
