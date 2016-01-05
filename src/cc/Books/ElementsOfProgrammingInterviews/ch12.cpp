
#include "ch12.hpp"

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

namespace {
  // 
}

namespace study {

  int BinarySearch(const std::vector<int> &data, int t) {
    if (data.empty())
      return -1;
    else if (data.size() == 1)
      return (data[0] == t) ? 0 : -1;
    size_t l {};
    size_t r {data.size()};
    size_t mid = (l + r) / 2;
    while (l - r > 1) {
      if (data[mid] == t)
        return (int)mid;
      else if (data[mid] < t)
        l = mid+1;
      else
        r = mid;
      mid = (l + r) / 2;
    }
    return data[l] == t ? (int)l : -1;
  }

  int SearchFirstOfK(const std::vector<int> &data, int k) {
    int result {-1};
    if (data.empty())
      return -1;
    else if (data.size() == 1)
      return (data[0] == k) ? 0 : -1;
    size_t l {};
    size_t r {data.size()};
    size_t mid = (l + r) / 2;
    while (l - r > 1) {
      if (data[mid] == k) {
        result = (int)mid;
        r = mid;
      }
      else if (data[mid] < k)
        l = mid+1;
      else
        r = mid;
      mid = (l + r) / 2;
    }
    return data[l] == k ? (int)l : result;
  }

  int SearchFirstLargerOfK(const std::vector<int> &data, int k) {
    if (data.empty())
      return -1;
    else if (data.size() == 1)
      return (data[0] == k) ? 0 : -1;
    size_t l {};
    size_t r {data.size()};
    size_t mid = (l + r) / 2;
    while (l - r > 1) {
      if (data[mid] <= k)
        l = mid+1;
      else
        r = mid;
      mid = (l + r) / 2;
    }
    if (data[l] > k)
      return (int)l;
    return (++l < data.size()) ? (int)l : -1;
  }

}
