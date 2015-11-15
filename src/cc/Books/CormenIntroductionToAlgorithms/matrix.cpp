
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <utility>

namespace study {

  template <int N>
  void print_arrays(int p[N+1], int m[N][N], int s[N][N]) {
    std::cout << "[p]\n";
    for (size_t i=0; i<=N; ++i)
      std::cout << p[i] << " ";
    std::cout << "\n";
    std::cout << "[m]\n";
    for (size_t i=0; i<N; ++i) {
      for (size_t j=0; j<N; ++j) {
        std::cout.width(5);
        std::cout << m[i][j] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "[s]\n";
    for (size_t i=0; i<N; ++i) {
      for (size_t j=0; j<N; ++j) {
        std::cout.width(2);
        std::cout << s[i][j] << " ";
      }
      std::cout << "\n";
    }
    std::cout << std::flush;
  }


  template <int N>
  void matrix_chain_order(int p[N+1], int m[N][N], int s[N][N]) {
    for (size_t i=0; i<N; ++i)
      m[i][i] = 0;
    for (size_t l=2; l<=N; ++l) {
      for (size_t i=0; i<N-l+1; ++i) {
        size_t j = i + l - 1;
        m[i][j] = std::numeric_limits<int>::max();
        for (size_t k=i; k<j; ++k) {
          int q = m[i][k] + m[k+1][j] + (p[i]*p[k+1]*p[j+1]);
          if (q < m[i][j]) {
            m[i][j] = q;
            s[i][j] = k;
          }
        }
      }
    }
  }

  template <int N>
  void print_optimal_parens(int s[N][N], size_t i, size_t j) {
    if (i == j)
      std::cout << "A" << i;
    else {
      std::cout << "(";
      print_optimal_parens(s, i, s[i][j]);
      print_optimal_parens(s, s[i][j]+1, j);
      std::cout << ")";
    }
  }

}
