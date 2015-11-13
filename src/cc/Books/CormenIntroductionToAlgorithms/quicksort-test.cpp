
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <vector>

#include "quicksort.hpp"

void test_partition() {
  std::vector<size_t> values;
  auto r = std::bind(std::uniform_int_distribution<>(), std::default_random_engine{});
  size_t n;
  for (size_t i=0; i<10000; ++i) {
    n = r() % 200;
    values.resize(n);
    generate(&values[0], &values[n], r);

    // partition:
    // every value before partion is less than or equal to the partition value
    // every value after partion is greater than or equal to the partition value
    size_t pi = study::partition(&values[0], 0, n);
    if (pi > 0 && pi < n) {
      auto lower_max_iter = std::max_element(&values[0], &values[pi]);
      auto upper_min_iter = std::min_element(&values[pi], &values[n]);
      assert(*lower_max_iter <= *upper_min_iter);
    }

  }
}


void test_nth_element() {
  std::vector<size_t> values, values2;
  auto r = std::bind(std::uniform_int_distribution<>(), std::default_random_engine{});
  size_t n;
  for (size_t i=0; i<10000; ++i) {
    n = (r() % 200) + 1;
    values.resize(n);
    generate(&values[0], &values[n], r);

    values2 = values;

    auto nth = study::nth_element(&values[0], 0, n, n/2);
    std::nth_element(&values2[0], &values2[n/2], &values2[n]);
    assert(nth == values2[n/2]);
  }

  n = 100;
  values.clear();
  values.resize(n);
  values2 = values;
  auto nth = study::nth_element(&values[0], 0, n, n/2);
  std::nth_element(&values2[0], &values2[n/2], &values2[n]);
  assert(nth == values2[n/2]);

}
