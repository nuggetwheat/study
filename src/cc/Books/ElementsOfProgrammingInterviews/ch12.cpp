
#include "ch12.hpp"
#include "reference/ch12.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

extern "C" {
#include <math.h>
}

using namespace std;

namespace study {

  int BinarySearch(const std::vector<int> &data, int t) {
    return reference::BinarySearch(data, t);
  }

  int SearchFirstOfK(const std::vector<int> &data, int k) {
    return reference::SearchFirstOfK(data, k);
  }

  int SearchFirstLargerOfK(const std::vector<int> &data, int k) {
    return reference::SearchFirstLargerOfK(data, k);
  }

  int SearchEntityEqualToItsIndex(const std::vector<int> &data) {
    return reference::SearchEntityEqualToItsIndex(data);
  }

  int SearchSmallest(const std::vector<int> &data) {
    return reference::SearchSmallest(data);
  }

  int SearchSmallestWithRepeated(const std::vector<int> &data) {
    return reference::SearchSmallestWithRepeated(data);
  }

  int SquareRoot(int k) {
    return reference::SquareRoot(k);
  }

  double SquareRoot(double k) {
    return reference::SquareRoot(k);
  }

  bool MatrixSearch(const std::vector<std::vector<int>> &A, int x) {
    return reference::MatrixSearch(A, x);
  }

  std::pair<int, int> FindMinMax(const std::vector<int> &A) {
    return reference::FindMinMax(A);
  }

  int FindKthLargest(std::vector<int> *A_ptr, size_t k) {
    return reference::FindKthLargest(A_ptr, k);
  }

  double MailBoxPlacement(const std::vector<int> &A) {
    return reference::MailBoxPlacement(A);
  }

  std::pair<int, int> FindDuplicateMissing(const std::vector<int> &A) {
    return reference::FindDuplicateMissing(A);
  }

}

