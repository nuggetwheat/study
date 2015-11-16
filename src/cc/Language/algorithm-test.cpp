
#include "algorithm.hpp"

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace {
  class MeanValue {
  public:
    void operator()(int elem) {
      ++count_;
      sum_ += elem;
    }
    operator double() {
      return static_cast<double>(sum_) / static_cast<double>(count_);
    }
  private:
    long count_ {};
    long sum_ {};
  };
  bool absLess(int elem1, int elem2) {
    return abs(elem1) < abs(elem2);
  }
}

namespace study {

  void test_for_each() {
    int total {};
    std::vector<int> values(10);
    std::iota(values.begin(), values.end(), 1);

    study::for_each(values.begin(), values.end(),
                    [&](int elem) {
                      total += elem;
                    });
    assert(total == (10*11)/2);

    double mean = study::for_each(values.begin(), values.end(), MeanValue());
    assert(mean == 5.5);

  }

  void test_count() {
    std::vector<int> values(9);
    std::iota(values.begin(), values.end(), 1);

    int n = study::count(values.begin(), values.end(), 4);
    assert(n == 1);
    n = study::count_if(values.begin(), values.end(),
                        [](int elem) {
                          return elem%2 == 0;
                        });
    assert(n == 4);
    auto pred = std::bind(std::logical_not<bool>(),
                          std::bind(std::modulus<int>(), std::placeholders::_1, 2));
    n = study::count_if(values.begin(), values.end(), pred);
    assert(n == 4);    
    n = study::count_if(values.begin(), values.end(),
                        [](int elem) {
                          return elem > 4;
                        });
    assert(n == 5);
  }

  void test_minmax() {
    std::vector<int> values(15, 1);
    std::iota(values.begin(), values.begin()+5, 1);
    std::iota(values.begin()+5, values.end(), -3);
    assert(*study::min_element(values.cbegin(), values.cend()) == -3);
    assert(*study::max_element(values.cbegin(), values.cend()) == 6);
    auto mm = study::minmax_element(values.cbegin(), values.cend());
    assert(*mm.first == -3);
    assert(*mm.second == 6);
    assert(std::distance(mm.first, mm.second) == 9);
    assert(*study::min_element(values.cbegin(), values.cend(), absLess) == 0);
    assert(*study::max_element(values.cbegin(), values.cend(), absLess) == 6);
  }

}
