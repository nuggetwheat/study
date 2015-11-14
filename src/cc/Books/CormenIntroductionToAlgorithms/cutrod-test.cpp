
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <vector>

#include "cutrod.hpp"

namespace study {

  void test_cutrod() {
    std::vector<int> price;
    auto r = std::bind(std::uniform_int_distribution<>(0, 30), std::default_random_engine{});
    for (size_t i=0; i<10000; ++i) {
      price.resize((r() % 50) + 1);
      generate(price.begin(), price.end(), r);
      int optimal_a = study::cutrod_topdown_memoized(price.data(), price.size());
      int optimal_b = study::cutrod_bottomup_memoized(price.data(), price.size());
      assert(optimal_a == optimal_b);
    }
  }

}
