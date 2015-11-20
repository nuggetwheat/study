
#include "algorithm.hpp"

#include <cassert>
#include <cstdlib>
#include <deque>
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
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
  bool checkEven(int elem, bool even) {
    return (elem % 2 == 0) ? even : !even;
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

  void test_find() {
    std::list<int> values(18);
    int val {};
    std::generate(values.begin(), values.end(),
                  [&]() -> int { return (val++%9)+1; });
    std::list<int>::iterator pos1, pos2;
    pos1 = study::find(values.begin(), values.end(), 4);
    if (pos1 != values.end())
      pos2 = study::find(++pos1, values.end(), 4);
    std::stringstream ss;
    if (pos1 != values.end() && pos2 != values.end())
      std::copy(--pos1, ++pos2, std::ostream_iterator<int>(ss, " "));
    assert(ss.str().compare("4 5 6 7 8 9 1 2 3 4 ") == 0);

    val = 0;
    values.resize(9);
    std::generate(values.begin(), values.end(),
                  [&]() -> int { return (val++%9)+1; });

    auto pos = study::find_if(values.begin(), values.end(),
                              std::bind(std::greater<int>(), std::placeholders::_1, 3));
    assert(std::distance(values.begin(), pos) + 1 == 4);

    pos = study::find_if(values.begin(), values.end(),
                         [](int elem) { return elem%3 == 0;});
    assert(std::distance(values.begin(), pos) + 1 == 3);

    pos = study::find_if_not(values.begin(), values.end(),
                             std::bind(std::less<int>(), std::placeholders::_1, 5));
    assert(*pos == 5);
                       
  }

  void test_search() {
    // search_n
    {
      std::deque<int> coll{ 1, 2, 7, 7, 6, 3, 9, 5, 7, 7, 7, 3, 6 };
      auto pos = study::search_n(coll.begin(), coll.end(), 3, 7);
      assert(std::distance(coll.begin(), pos) == 8);
      pos = study::search_n(coll.begin(), coll.end(), 4, 0,
                            [](int elem, int value) {
                              return elem%2==1;
                            });
      assert(std::distance(coll.begin(), pos) == 5);
    }
    // search
    {
      std::deque<int> coll(14);
      std::list<int> subcoll(4);
      std::vector<int> result;
      int val {};
      std::generate(coll.begin(), coll.end(),
                    [&val]() -> int { return (val++%7)+1; });
      std::iota(subcoll.begin(), subcoll.end(), 3);
      auto pos = study::search(coll.begin(), coll.end(), subcoll.begin(), subcoll.end());
      while (pos != coll.end()) {
        result.push_back(std::distance(coll.begin(), pos));
        pos = study::search(++pos, coll.end(), subcoll.begin(), subcoll.end());
      }
      assert(result.size() == 2);
      assert(result[0] == 2);
      assert(result[1] == 9);

      std::vector<int> coll2(9);
      std::iota(coll2.begin(), coll2.end(), 1);
      result.clear();
      bool checkEvenArgs[3] = { true, false, true };
      auto pos2 = study::search(coll2.begin(), coll2.end(), checkEvenArgs, checkEvenArgs+3, checkEven);
      while (pos2 != coll2.end()) {
        result.push_back(std::distance(coll2.begin(), pos2));
        pos2 = study::search(++pos2, coll2.end(), checkEvenArgs, checkEvenArgs+3, checkEven);
      }
      assert(result.size() == 3);
      assert(result[0] == 1);
      assert(result[1] == 3);
      assert(result[2] == 5);
    }

    // mismatch
    {
      std::vector<int> coll1 = { 1, 2, 3, 4, 5, 6 };
      std::list<int> coll2 = { 1, 2, 4, 8, 16, 3 };
      auto values = study::mismatch(coll1.begin(), coll1.end(),
                                    coll2.begin());
      assert(*values.first == 3 && *values.second == 4);
      values = study::mismatch(coll1.begin(), coll1.end(),
                               coll2.begin(), std::less_equal<int>());
      assert(*values.first == 6 && *values.second == 3);
    }
  }

}
