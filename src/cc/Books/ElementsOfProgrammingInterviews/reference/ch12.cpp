
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

namespace reference {

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

  int SearchEntityEqualToItsIndex(const std::vector<int> &data) {
    if (data.empty())
      return -1;
    else if (data.size() == 1)
      return (data[0] == 0) ? 0 : -1;
    size_t l {};
    size_t r {data.size()};
    size_t mid = (l + r) / 2;
    while (l - r > 1) {
      if (data[mid] == (int)mid)
        return (int)mid;
      else if (data[mid] < (int)mid)
        r = mid;
      else
        l = mid+1;
      mid = (l + r) / 2;
    }
    return data[l] == (int)l ? (int)l : -1;
  }

  int SearchSmallest(const std::vector<int> &data) {
    if (data.empty())
      return -1;
    else if (data.size() == 1)
      return 0;
    int l {}, r = data.size() - 1;
    while (l < r) {
      int mid = l + ((r -l) / 2);
      if (data[mid] > data[r])
        l = mid + 1;
      else
        r = mid;
    }
    return l;
  }

  int searchSmallestWithRepeated(const std::vector<int> &data, int left, int right) {
    if (left == right)
      return left;
    int mid = left + ((right - left) / 2);
    if (data[left] < data[right])
      return searchSmallestWithRepeated(data, left, mid);
    auto left_result = searchSmallestWithRepeated(data, left, mid);
    auto right_result = searchSmallestWithRepeated(data, mid+1, right);
    return (data[left_result] < data[right_result]) ? left_result : right_result;
  }

  int SearchSmallestWithRepeated(const std::vector<int> &data) {
    if (data.empty())
      return -1;
    else if (data.size() == 1)
      return 0;
    return searchSmallestWithRepeated(data, 0, (int)data.size()-1);
  }

  int squareRootHelper(int k, int small, int large) {
    if (small == large)
      return small;
    int mid = small + large;
    if (mid & 1)
      ++mid;
    mid /= 2;
    int mid_squared = mid*mid;
    if (mid_squared == k)
      return mid;
    else if (mid_squared < k)
      return squareRootHelper(k, mid, large);
    return squareRootHelper(k, small, mid-1);
  }

  int SquareRoot(int k) {
    return squareRootHelper(k, 1, k/2);
  }

  int compare(double a, double b) {
    double diff = (a - b) / b;
    if (diff < -numeric_limits<double>::epsilon())
      return -1;
    else if (diff > numeric_limits<double>::epsilon())
      return 1;
    return 0;
  }

  double SquareRoot(double k) {
    double left, right;
    if (k < 1.0) {
      left = k;
      right = 1.0;
    }
    else {
      left = 1.0;
      right = k;
    }

    while (compare(left, right) < 0) {
      double mid = (left + right) / 2.0;
      double mid_squared = mid*mid;
      int cmp = compare(mid_squared, k);
      if (cmp == 0)
        return mid;
      else if (cmp < 0)
        left = mid;
      else
        right = mid;
    }
    return left;
  }

  bool MatrixSearch(const std::vector<std::vector<int>> &A, int x) {
    if (A.empty())
      return false;
    int row = 0, col = A[0].size() - 1;
    while (row < (int)A.size() && col >= 0) {
      if (A[row][col] == x)
        return true;
      else if (A[row][col] > x)
        --col;
      else
        ++row;
    }
    return false;
  }

  std::pair<int, int> FindMinMax(const std::vector<int> &A) {
    assert(!A.empty());
    if (A.size() == 1)
      return { A.front(), A.front() };
    std::pair<int, int> global = minmax(A[0], A[1]);
    for (size_t i=2; i<A.size()-1; i+=2) {
      std::pair<int, int> local = minmax(A[i], A[i+1]);
      global.first  = min(global.first, local.first);
      global.second = max(global.second, local.second);
    }
    if (A.size() & 1)
      global = {min(global.first, A.back()), max(global.second, A.back())};
    return global;
  }

  size_t partition(std::vector<int> *A_ptr, size_t low, size_t high) {
    std::vector<int> &A = *A_ptr;
    if (low == high-1)
      return low;
    size_t end = high--;
    int pval = A[high];
    while (low < end && A[low] < pval)
      ++low;
    while (high > low && A[high] > pval)
      --high;
    while (low < high) {
      swap(A[low++], A[high--]);
      while (low < end && A[low] < pval)
        ++low;
      while (high > low && A[high] > pval)
        --high;
    }
    return low;
  }

  int FindKthLargest(std::vector<int> *A_ptr, size_t k) {
    std::vector<int> &A = *A_ptr;
    size_t low {};
    size_t high {A.size()};
    size_t mid;
    while (low < (high-1)) {
      mid = partition(A_ptr, low, high);
      if (mid > k)
        high = mid;
      else
        low = mid;
    }
    return A[low];
  }

  double MailBoxPlacement(const std::vector<int> &A) {
    int total_people {};
    int total_weight {};
    for (int i=0; i<(int)A.size(); ++i) {
      if (A[i]) {
        total_people += A[i];
        total_weight += i*A[i];
      }
    }
    return (double)total_weight / (double)total_people;
  }

  std::pair<int, int> FindDuplicateMissing(const std::vector<int> &A) {
    int all_xor {};
    for (int i=0; i<(int)A.size(); ++i)
      all_xor ^= A[i] ^ i;

    int bitmask = all_xor & (~(all_xor-1));
    int matching_xor {};
    for (int i=0; i<(int)A.size(); ++i) {
      if (i & bitmask)
        matching_xor ^= i;
      if (A[i] & bitmask)
        matching_xor ^= A[i];
    }

    for (auto val : A) {
      if (val == matching_xor)
        return {matching_xor, matching_xor ^ all_xor};
    }
    return {matching_xor ^ all_xor, matching_xor};    
  }


}

