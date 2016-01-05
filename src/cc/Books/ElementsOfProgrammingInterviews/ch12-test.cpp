
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "ch12.hpp"

using namespace std;
using namespace study;

namespace {

  void testBinarySearch() {
    cout << "[ch12] BinarySearch" << endl;
    vector<int> data({-14, -10, 2, 108, 108, 243, 285, 285, 285, 401});
    assert(BinarySearch(data, -14) == 0);
    assert(BinarySearch(data, -10) == 1);
    assert(BinarySearch(data, 2) == 2);
    int index = BinarySearch(data, 108);
    assert(index == 3 || index == 4);
    assert(BinarySearch(data, 243) == 5);
    index = BinarySearch(data, 285);
    assert(index == 6 || index == 7 || index == 8);
    assert(BinarySearch(data, 401) == 9);
    assert(BinarySearch(data, -113) == -1);
    assert(BinarySearch(data, 3113) == -1);
    assert(BinarySearch(data, 284) == -1);
  }

  void testSearchFirstOfK() {
    cout << "[ch12] SearchFirstOfK" << endl;
    vector<int> data({-14, -10, 2, 108, 108, 243, 285, 285, 285, 401});
    assert(SearchFirstOfK(data, -15) == -1);
    assert(SearchFirstOfK(data, -14) == 0);
    assert(SearchFirstOfK(data, 108) == 3);
    assert(SearchFirstOfK(data, 285) == 6);
    assert(SearchFirstOfK(data, 401) == 9);
    assert(SearchFirstOfK(data, 402) == -1);
  }

  void testSearchFirstLargerOfK() {
    cout << "[ch12] SearchFirstLargerOfK" << endl;
    vector<int> data({-14, -10, 2, 108, 108, 243, 285, 285, 285, 401});
    assert(SearchFirstLargerOfK(data, -15) == 0);
    assert(SearchFirstLargerOfK(data, -14) == 1);
    assert(SearchFirstLargerOfK(data, -10) == 2);
    assert(SearchFirstLargerOfK(data, 2) == 3);
    assert(SearchFirstLargerOfK(data, 108) == 5);
    assert(SearchFirstLargerOfK(data, 243) == 6);
    assert(SearchFirstLargerOfK(data, 285) == 9);
    assert(SearchFirstLargerOfK(data, 401) == -1);
  }

}


namespace study {

  void ch12_test() {
    testBinarySearch();
    testSearchFirstOfK();
    testSearchFirstLargerOfK();
  }

}


