
#include "ch6.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <utility>

extern "C" {
#include <math.h>
}

namespace {
  std::default_random_engine dre;
}

namespace reference {

  void DutchFlagPartition(size_t pivot_index, std::vector<int> *A_ptr) {
    std::vector<int> &A = *A_ptr;
    int pivot = A[pivot_index];
    size_t low = 0, equal = 0, high = A.size();
    while (equal < high) {
      if (A[equal] < pivot)
        std::swap(A[equal++], A[low++]);
      else if (A[equal] == pivot)
        ++equal;
      else
        std::swap(A[equal], A[--high]);
    }
    // verify
    size_t i=0;
    while (i < A.size() && A[i] < pivot)
      ++i;
    while (i < A.size() && A[i] == pivot)
      ++i;
    while (i < A.size()) {
      assert(A[i] > pivot);
      ++i;
    }
  }


  std::vector<int> PlusOne(std::vector<int> A) {
    if (A.empty())
      A.push_back(1);
    else {
      ++(A.back());
      for (size_t i=A.size()-1; i>0 && A[i] == 10; --i) {
        A[i] = 0;
        ++A[i-1];
      }
      if (A.front() == 10) {
        A.front() = 0;
        A.insert(A.begin(), 1);
      }
    }
    return A;
  }

  std::vector<int> Multiply(std::vector<int> num1, std::vector<int> num2) {
    assert(!num1.empty() && !num2.empty());
    bool isNegative = (num1.front() < 0 && num2.front() >= 0) ||
      (num2.front() < 0 && num1.front() >= 0);
    num1.front() = abs(num1.front());
    num2.front() = abs(num2.front());
    std::vector<int> result(num1.size()+num2.size());
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    for (size_t i=0; i<num1.size(); ++i) {
      for (size_t j=0; j<num2.size(); ++j) {
        result[i+j] += num1[i] * num2[j];
        result[i+j+1] += result[i+j] / 10;
        result[i+j] %= 10;
      }
    }
    size_t newSize = result.size();
    while (newSize > 1 && result[newSize-1] == 0)
      --newSize;
    result.resize(newSize);
    std::reverse(result.begin(), result.end());
    if (isNegative)
      result.front() *= -1;
    return result;
  }

  bool CanReachEnd(const std::vector<int> &max_advance_steps) {
    size_t furthest_reach_so_far {};
    auto last_index = max_advance_steps.size() - 1;
    for (size_t i=0; i<=furthest_reach_so_far && furthest_reach_so_far<last_index; ++i)
      furthest_reach_so_far = std::max(furthest_reach_so_far, i+max_advance_steps[i]);
    return furthest_reach_so_far >= last_index;
  }

  size_t FewestStepsToEnd(const std::vector<int> &max_advance_steps) {
    std::vector<int> min_source_position(max_advance_steps.size(),
                                         std::numeric_limits<int>::max());
    min_source_position[0] = 0;
    auto last_index = max_advance_steps.size() - 1;
    for (int i=0; i<(int)last_index; ++i) {
      if (min_source_position[i] != std::numeric_limits<int>::max()) {
        for (int j=1; (i+j)<(int)max_advance_steps.size() && j<=max_advance_steps[i]; ++j)
          min_source_position[i+j] = std::min(min_source_position[i+j], i);
      }
    }
    if (min_source_position[last_index] == std::numeric_limits<int>::max())
      return std::numeric_limits<int>::max();
    size_t steps = 0;
    for (auto offset=last_index; offset>0; offset = min_source_position[offset])
      ++steps;
    return steps;
  }

  size_t DeleteKey(int key, std::vector<int> *A_ptr) {
    std::vector<int> &A = *A_ptr;
    size_t dst {};
    for (size_t src=0; src<A.size(); ++src) {
      if (A[src] != key)
        A[dst++] = A[src];
    }
    return dst;
  }

  int DeleteDuplicates(std::vector<int> *A_ptr) {
    std::vector<int> &A = *A_ptr;
    if (A.empty())
      return 0;
    size_t i=0;
    for (size_t j=1; j<A.size(); ++j) {
      if (A[i] != A[j])
        A[++i] = A[j];
    }
    return i+1;
  }

  int BuyAndSellStockOnce(const std::vector<int> &prices) {
    int bestGain {};
    size_t lowest_prior {};
    for (size_t i=1; i<prices.size(); ++i) {
      if (prices[i] < prices[lowest_prior])
        lowest_prior = i;
      else if (prices[i] - prices[lowest_prior] > bestGain)
        bestGain = prices[i] - prices[lowest_prior];
    }
    return bestGain;
  }

  int BuyAndSellStockTwice(const std::vector<int> &prices) {
    std::vector<int> bestForwardGain(prices.size());
    size_t lowest_prior {};
    int best = 0, bestForward = 0, bestReverse = 0;
    for (size_t i=1; i<prices.size(); ++i) {
      if (prices[i] < prices[lowest_prior]) {
        lowest_prior = i;
        bestForwardGain[i] = bestForwardGain[i-1];
      }
      else if (prices[i] - prices[lowest_prior] > bestForwardGain[i-1])
        bestForwardGain[i] = prices[i] - prices[lowest_prior];
      else
        bestForwardGain[i] = bestForwardGain[i-1];
      bestForward = std::max(bestForward, bestForwardGain[i]);
    }
    int highest_prior = (int)prices.size() - 1;
    for (int i=highest_prior-1; i>0; --i) {
      if (prices[i] > prices[highest_prior])
        highest_prior = i;
      else if (prices[highest_prior] - prices[i] > bestReverse)
        bestReverse = prices[highest_prior] - prices[i];
      best = std::max(best, bestReverse+bestForwardGain[i-1]);
    }
    return std::max(best, bestForward);
  }

  std::vector<int> GeneratePrimes(int n) {
    std::vector<int> primes;
    std::vector<bool> is_prime(n+1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i=2; i<n; ++i) {
      if (is_prime[i]) {
        primes.push_back(i);
        for (int j=i*2; j<=n; j+=i)
          is_prime[j] = false;
      }
    }
    return primes;
  }

  void ApplyPermutation(std::vector<int> perm, std::vector<int> *A_ptr) {
    std::vector<int> &A = *A_ptr;
    for (int i=0; i < (int)perm.size(); ++i) {
      int j = i;
      while (perm[j] >= 0) {
        std::swap(A[i], A[perm[j]]);
        int prevj = j;
        j = perm[j];
        perm[prevj] -= (int)perm.size();
      }
    }
  }

  std::vector<int> NextPermutation(std::vector<int> perm) {
    std::vector<int> next = perm;
    size_t k = perm.size() - 1;
    while (k > 0 && perm[k-1] > perm[k])
      --k;
    if (k == 0)
      next.clear();
    else {
      size_t i = k--;
      while (i < perm.size()-1 && perm[i+1] > perm[k])
        ++i;
      std::swap(next[k], next[i]);
      for (size_t f=k+1, b=next.size()-1; f<b; ++f, --b)
        std::swap(next[f], next[b]);
    }
    return next;
  }

  std::vector<int> PrevPermutation(std::vector<int> perm) {
    std::vector<int> prev = perm;
    size_t k = perm.size() - 1;
    while (k > 0 && perm[k-1] < perm[k])
      --k;
    if (k == 0)
      prev.clear();
    else {
      --k;
      // reverse the suffix
      for (size_t f=k+1, b=prev.size()-1; f<b; ++f, --b)
        std::swap(prev[f], prev[b]);
      size_t i = k+1;
      while (i < perm.size()-1 && perm[i+1] > perm[k])
        ++i;
      std::swap(prev[k], prev[i]);
    }
    return prev;
  }

  std::vector<int> ComputeRandomPermutation(int n) {
    std::vector<int> data(n);
    if (n > 0) {
      iota(data.begin(), data.end(), 0);
      std::default_random_engine re(42);
      for (size_t i=0; i<(size_t)n-1; ++i) {
        std::uniform_int_distribution<int> dist(0, (n-1)-i);
        std::swap(data[i], data[dist(re)]);
      }
    }
    return data;
  }

  std::vector<int> ComputeRandomSubset(int n, int k) {
    std::vector<int> data(k);
    assert(k <= n);
    if (k > 0) {
      std::unordered_map<int, int> chosen;
      std::default_random_engine re(42);
      re.discard(1);
      std::uniform_int_distribution<int> dist(0, (n-1));
      for (int i=0; i<k; ++i) {
        auto key = dist(re);
        auto iter_k = chosen.find(key);
        auto iter_i = chosen.find(i);
        if (iter_k == chosen.end() && iter_i == chosen.end()) {
          chosen[i] = key;
          chosen[key] = i;
        }
        else if (iter_k == chosen.end() && iter_i != chosen.end()) {
          chosen[key] = iter_i->second;
          iter_i->second = key;
        }
        else if (iter_k != chosen.end() && iter_i == chosen.end()) {
          chosen[i] = iter_k->second;
          iter_i->second = i;
        }
        else {
          auto tmp = iter_i->second;
          iter_i->second = key;
          chosen[i] = tmp;
        }
      }
      std::iota(data.begin(), data.end(), 0);
      std::transform(data.cbegin(), data.cend(), data.begin(),
                     [&chosen](int elem) { return chosen[elem]; });
    }
    return data;
  }

  void RotateMatrix(std::vector<std::vector<int>> *square_matrix_ptr) {
    std::vector<std::vector<int>> &A = *square_matrix_ptr;
    for (size_t first = 0; first < A.size()/2; ++first) {
      size_t last = (A.size()-first)-1;
      size_t max_offset = last - first;
      for (size_t i=0; i<max_offset; ++i) {
        auto front = i+first;
        auto back = last-i;
        auto tmp = A[first][front];
        A[first][front] = A[back][first];
        A[back][first] = A[last][back];
        A[last][back] = A[front][last];
        A[front][last] = tmp;
      }
    }
  }

}
