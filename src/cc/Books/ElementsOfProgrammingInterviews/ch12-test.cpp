
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

  void testSearchEntityEqualToItsIndex() {
    cout << "[ch12] SearchEntityEqualToItsIndex" << endl;
    vector<int> data({-2, 0, 2, 3, 6, 7, 9});
    assert(SearchEntityEqualToItsIndex(data) == 3);
    data = {2, 2, 2, 2, 2, 2, 2};
    assert(SearchEntityEqualToItsIndex(data) == 2);
    data = {3, 3, 3, 3, 3, 3, 3};
    assert(SearchEntityEqualToItsIndex(data) == 3);
  }

  void testSearchSmallest() {
    cout << "[ch12] SearchSmallest" << endl;
    vector<int> data({378, 478, 550, 631, 103, 203, 220, 234, 279, 368});
    assert(SearchSmallest(data) == 4);
    data = {10, 11, 1, 2, 3, 4, 5, 6, 7};
    assert(SearchSmallestWithRepeated(data) == 2);
    data = {6, 7, 8, 9, 10, 11, 1, 2, 3};
    assert(SearchSmallestWithRepeated(data) == 6);
    data = {1, 1, 1, 1, 1, 0, 1, 1, 1};
    assert(SearchSmallestWithRepeated(data) == 5);
    data = {1, 1, 1, 0, 1, 1, 1, 1, 1};
    assert(SearchSmallestWithRepeated(data) == 3);
    data = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    assert(SearchSmallestWithRepeated(data) != -1);
  }

  void testSquareRoot() {
    cout << "[ch12] SquareRoot" << endl;
    vector<int> expected({1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6});
    vector<int> results;
    for (int i=1; i<38; ++i)
      results.push_back(SquareRoot(i));
    assert(results == expected);
    stringstream ss;
    ss << SquareRoot(2.0);
    assert(ss.str() == "1.41421");
    ss.str( std::string() );
    ss.clear();
    ss << SquareRoot(5.0);
    assert(ss.str() == "2.23607");
    ss.str( std::string() );
    ss.clear();
  }

  void testMatrixSearch() {
    cout << "[ch12] MatrixSearch" << endl;
    vector<vector<int>> matrix;
    matrix.push_back({-1, 2, 4, 4, 6});
    matrix.push_back({1, 5, 5, 9, 21});
    matrix.push_back({3, 6, 6, 9, 22});
    matrix.push_back({3, 6, 8, 10, 24});
    matrix.push_back({6, 8, 9, 12, 25});
    matrix.push_back({8, 10, 12, 13, 40});
    assert(MatrixSearch(matrix, 5));
    assert(MatrixSearch(matrix, -1));
    assert(MatrixSearch(matrix, 8));
    assert(MatrixSearch(matrix, 13));
    assert(MatrixSearch(matrix, 24));
    assert(!MatrixSearch(matrix, 0));
    assert(!MatrixSearch(matrix, 7));
    assert(!MatrixSearch(matrix, 11));
    assert(!MatrixSearch(matrix, 50));
  }

  void testFindMinMax() {
    cout << "[ch12] FindMinMax" << endl;
    vector<int> data {3, 2, 5, 1, 2, 4};
    assert(FindMinMax(data) == make_pair(1, 5));
  }

  void testFindKthLargest() {
    cout << "[ch12] FindKthLargest" << endl;
    vector<int> expected {1, 1, 2, 2, 4, 5, 5};
    vector<int> input {1, 4, 5, 5, 1, 2, 2};
    vector<int> result;
    for (size_t i=0; i<input.size(); ++i)
      result.push_back(FindKthLargest(&input, i));
    assert(result == expected);
    expected = {0, 1, 2, 3, 4, 5, 6};
    input = {4, 5, 1, 6, 2, 0, 3};
    result.clear();
    for (size_t i=0; i<input.size(); ++i)
       result.push_back(FindKthLargest(&input, i));
    assert(result == expected);
  }

  void testMailBoxPlacement() {
    cout << "[ch12] MailBoxPlacement" << endl;
    vector<int> data {0, 0, 0, 0, 5};
    assert(MailBoxPlacement(data) == 4.0);
    data = {5, 0, 0, 0, 5};
    assert(MailBoxPlacement(data) == 2.0);
    data = {5, 0, 5, 0, 5};
    assert(MailBoxPlacement(data) == 2.0);
    data = {5, 0, 0, 0, 0};
    assert(MailBoxPlacement(data) == 0.0);
    data = {0, 0, 10, 0, 10};
    assert(MailBoxPlacement(data) == 3.0);
    data = {10, 0, 10, 0, 0};
    assert(MailBoxPlacement(data) == 1.0);
  }

  void testFindDuplicateMissing() {
    cout << "[ch12] FindDuplicateMissing" << endl;
    vector<int> data {5, 3, 0, 3, 1, 2};
    assert(FindDuplicateMissing(data) == make_pair(3, 4));
  }

}


namespace study {

  void ch12_test() {
    testBinarySearch();
    testSearchFirstOfK();
    testSearchFirstLargerOfK();
    testSearchEntityEqualToItsIndex();
    testSearchSmallest();
    testSquareRoot();
    testMatrixSearch();
    testFindMinMax();
    testFindKthLargest();
    testMailBoxPlacement();
    testFindDuplicateMissing();
  }

}


