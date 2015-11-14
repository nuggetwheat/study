
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "cutrod.hpp"

namespace study {

  int cutrod(int *price, size_t n) {
    if (n == 0)
      return 0;
    int q = std::numeric_limits<int>::min();
    for (size_t i=0; i<n; ++i)
      q = std::max(q, price[i] + cutrod(price, n-i-1));
    return q;
  }

  int cutrod_topdown_memoized_aux(int *price, size_t n, int *solved) {
    if (solved[n] >= 0)
      return solved[n];
    int q = n ? std::numeric_limits<int>::min() : 0;
    for (size_t i=0; i<n; ++i)
      q = std::max(q, price[i] + cutrod_topdown_memoized_aux(price, (n-1)-i, solved));
    solved[n] = q;
    return q;
  }

  int cutrod_topdown_memoized(int *price, size_t n) {
    std::vector<int> solved(n+1, std::numeric_limits<int>::min());
    return cutrod_topdown_memoized_aux(price, n, solved.data());
  }

  int cutrod_bottomup_memoized(int *price, size_t n) {
    std::vector<int> solved(n+1, 0);
    int q;
    for (size_t j=1; j<=n; ++j) {
      q = std::numeric_limits<int>::min();
      for (size_t i=0; i<j; ++i)
        q = std::max(q, price[i] + solved[j-1-i]);
      solved[j] = q;
    }
    return solved[n];
  }



}
