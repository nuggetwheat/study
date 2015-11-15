
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <vector>

#include "matrix.hpp"

using namespace std;

namespace {
  constexpr int pn = 6;
  int p[pn+1] = { 30, 35, 15, 5, 10, 20, 25 };
}

namespace study {

  void test_matrix() {
    cout << "[matrix]" << endl;
    int m[pn][pn];
    int s[pn][pn];
    for (size_t i=0; i<pn; ++i) {
      for (size_t j=0; j<pn; ++j) {
        m[i][j] = s[i][j] = -1;
      }
    }

    matrix_chain_order<pn>(p, m, s);
    cout << m[0][pn-1] << endl;

    print_optimal_parens(s, 0, pn-1);
    cout << endl;

    //print_arrays<pn>(p, m, s);

  }

}
