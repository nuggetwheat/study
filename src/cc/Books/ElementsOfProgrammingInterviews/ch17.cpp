
#include "ch17.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace {
  // 
}

namespace study {

  size_t FibonacciRecursive(size_t nth) {
    if (nth <= 2)
      return nth - 1;
    return FibonacciRecursive(nth-2) + FibonacciRecursive(nth-1);
  }

  size_t fibonacciDynamic(size_t nth, vector<int> *precomputed) {
    if ((*precomputed)[nth-1] == -1)
      (*precomputed)[nth-1] = fibonacciDynamic(nth-1, precomputed);
    if ((*precomputed)[nth-2] == -1)
      (*precomputed)[nth-2] = fibonacciDynamic(nth-2, precomputed);
    return (*precomputed)[nth-1] + (*precomputed)[nth-2];
  }

  size_t FibonacciDynamic(size_t nth) {
    assert(nth > 0);
    if (nth <= 2)
      return nth - 1;
    vector<int> precomputed(nth, -1);
    precomputed[1] = 0;
    precomputed[2] = 1;
    return fibonacciDynamic(nth, &precomputed);
  }

  pair<int, int> FindMaximumSubarray(const vector<int> &A) {
    pair<int, int> range(0, 0);
    size_t min_offset {0};
    int sum {}, min_sum {}, max_sum {};
    
    for (size_t i=0; i<A.size(); ++i) {
      sum += A[i];
      if (sum < min_sum) {
        min_offset = i+1;
        min_sum = sum;
      }
      if (sum - min_sum > max_sum) {
        range = {min_offset, i+1};
        max_sum = sum - min_sum;
      }
    }
    return range;
  }

  int CountCombinations(int total_score, const vector<int> &ways) {
    vector<int> combinations(total_score+1, 0);
    combinations[0] = 1;
    for (auto score : ways) {
      for (int j=score; j<=total_score; ++j)
        combinations[j] += combinations[j - score];
    }
    return combinations[total_score];
  }

  int CountPermutations(int total_score, const vector<int> &ways) {
    vector<int> permutations(total_score+1, 0);
    permutations[0] = 1;
    for (int i=0; i<=total_score; ++i) {
      for (auto score : ways) {
        if (i >= score)
          permutations[i] += permutations[i - score];
      }
    }
    return permutations[total_score];
  }

  int EditDistance(const string &A, const string &B) {
    vector<vector<int>> D(A.size()+1);
    for (size_t i=0; i<D.size(); ++i) {
      D[i].resize(B.size()+1);
      D[i][0] = i;
    }
    iota(D[0].begin(), D[0].end(), 0);
    for (size_t i=1; i<=A.size(); ++i) {
      for (size_t j=1; j<=B.size(); ++j) {
        if (A[i-1] == B[j-1])
          D[i][j] = D[i-1][j-1];
        else
          D[i][j] = 1 + min(D[i-1][j-1], min(D[i][j-1], D[i-1][j]));
      }
    }
    return D[A.size()][B.size()];
  }

  int EditDistanceOptimized(string A, string B) {
    if (A.size() < B.size())
      swap(A, B);
    vector<int> D(B.size()+1);
    iota(D.begin(), D.end(), 0);
    for (size_t i=1; i<=A.size(); ++i) {
      int pre_i_1_j_1 = D[0];
      D[0] = i;
      for (size_t j=1; j<=B.size(); ++j) {
        int pre_i_1_j = D[j];
        D[j] = A[i-1] == B[j-1] ? pre_i_1_j_1 :
          1 + min(pre_i_1_j_1, min(D[j-1], D[j]));
        pre_i_1_j_1 = pre_i_1_j;
      }
    }
    return D[B.size()];
  }

  int MinimumRemovalsToPalindrome(string str) {
    vector<vector<int>> D(str.size()+1);
    for (size_t i=0; i<=str.size(); ++i) {
      D[i].resize(str.size()+1);
      D[i][0] = i;
    }
    iota(D[0].begin(), D[0].end(), 0);
    for (size_t i=str.size(); i>=1; --i) {
      for (size_t j=i+1; j<=str.size(); ++j) {
        if (str[i-1] == str[j-1])
          D[i][j] = (j-i <= 2) ? 0 : D[i+1][j-1];
        else
          D[i][j] = 1 + ((j-i < 1) ? 0 : min(D[i+1][j], D[i][j-1]));
      }
    }
    return D[1][str.size()];
  }

  int NumberOfWaysToTraverse2DArray(int n, int m) {
    vector<vector<int>> counts(n+1);
    for (int i=0; i<(int)counts.size(); ++i)
      counts[i].resize(m+1, 0);
    for (int i=1; i<=n; ++i) {
      for (int j=1; j<=m; ++j)
        counts[i][j] = max(1, counts[i-1][j] + counts[i][j-1]);
    }
    return counts[n][m];
  }

  int NumberOfWaysToTraverse2DArrayOptimized(int n, int m) {
    vector<int> counts(m, 1);

    for (int i=1; i<n; ++i) {
      int prev_res = 0;
      for (int j=0; j<m; ++j) {
        counts[j] = counts[j] + prev_res;
        prev_res = counts[j];
      }
    }
    return counts[m-1];
  }

  int CountMonotone(int k) {
    vector<vector<int>> C(k);
    for (auto & row : C)
      row.resize(k);
    fill(C[0].begin(), C[0].end(), 1);
    for (int i=1; i<k; ++i) {
      for (int j=0; j<k; ++j) {
        for (int idx=0; idx<=j; ++idx)
          C[i][j] += C[i-1][idx];
      }
    }
    int result {};
    for (int i=0; i<k; ++i)
      result += C[k-1][i];
    return result;
  }

  int CountMonotoneOptimized(int k) {
    vector<int> C(k, 1);
    for (int i=1; i<k; ++i) {
      auto prior_row(C);
      for (int j=0; j<k; ++j) {
        C[j] = 0;
        for (int idx=0; idx<=j; ++idx) {
          C[j] += prior_row[idx];
        }
      }
    }
    int result {};
    for (int i=0; i<k; ++i)
      result += C[i];
    return result;
  }

  int MaximizeFishing(std::vector<std::vector<int>> &sea) {
    vector<int> bounty(sea[0].size());
    for (size_t i=0; i<bounty.size(); ++i) {
      for (size_t j=0; j<=i; ++j)
        bounty[i] += sea[0][j];
    }
    for (size_t i=1; i<bounty.size(); ++i) {
      int prev_left = 0;
      for (size_t j=0; j<bounty.size(); ++j) {
        int prev_up = bounty[j];
        bounty[j] = sea[i][j] + max(prev_left, prev_up);
        prev_left = bounty[j];
      }
    }
    return bounty.back();
  }

  struct HashTuple {
    size_t operator()(const tuple<int, int, int> &tuple) const {
      return hash<int>()(get<0>(tuple)) ^ hash<int>()(get<1>(tuple)) ^
        hash<int>()(get<2>(tuple));
    }
  };

  bool matchHelper(const vector<vector<int>> &A, const vector<int> &S,
                   int i, int j, int len,
                   unordered_set<tuple<int, int, int>, HashTuple> *cache) {
    if (len == (int)S.size())
      return true;
    if (i < 0 || i == (int)A.size() || j < 0 || j == (int)A[0].size())
      return false;
    if (A[i][j] == S[len] &&
        (matchHelper(A, S, i+1, j, len+1, cache) ||
         matchHelper(A, S, i-1, j, len+1, cache) ||
         matchHelper(A, S, i, j+1, len+1, cache) ||
         matchHelper(A, S, i, j-1, len+1, cache)))
      return true;
    cache->insert(make_tuple(i, j, len));
    return false;
  }

  bool Match(const vector<vector<int>> &A, const vector<int> &S) {
    unordered_set<tuple<int, int, int>, HashTuple> cache;
    for (int i=0; i<(int)A.size(); ++i) {
      for (int j=0; j<(int)A[0].size(); ++j) {
        if (matchHelper(A, S, i, j, 0, &cache))
          return true;
      }
    }
    return false;
  }

  int knapsackHelper(int capacity, const vector<Item> &items, vector<bool> *available) {
    int max_value {};
    for (size_t i=0; i<items.size(); ++i) {
      if (items[i].weight <= capacity && (*available)[i]) {
        (*available)[i] = false;
        int value = knapsackHelper(capacity - items[i].weight, items, available);
        if (value + items[i].value > max_value)
          max_value = value + items[i].value;
        (*available)[i] = true;
      }
    }
    return max_value;
  }

  int Knapsack(int capacity, const vector<Item> &items) {
    vector<bool> available(items.size(), true);
    return knapsackHelper(capacity, items, &available);
  }

  int KnapsackOptimized(int capacity, const std::vector<Item> &items) {
    vector<int> value(capacity+1, 0);
    for (size_t i=0; i<items.size(); ++i) {
      for (int j=capacity; j>=items[i].weight; --j) {
        value[j] = max(value[j], value[j - items[i].weight] + items[i].value);
      }
    }
    return value[capacity];
  }

  int MinimizeDifference(const std::vector<int> &A) {

    int total {};
    for (auto value : A)
      total += value;

    unordered_set<int> valid_sums;
    valid_sums.insert(0);

    for (auto value : A) {
      for (int v = total/2; v >= value; --v) {
        if (valid_sums.find(v - value) != valid_sums.end())
          valid_sums.insert(v);
      }
    }

    for (int i=total/2; i>=0; --i) {
      if (valid_sums.find(i) != valid_sums.end())
        return (total - i) - i;
    }
    return total;
  }

    bool wordBreakingHelper(const string &s,
                            const unordered_set<string> &dict,
                            vector<string> *words) {
      if (s.empty())
        return true;
      for (size_t i=1; i<=s.size(); ++i) {
        string candidate(s.substr(0, i));
        if (dict.find(candidate) != dict.end()) {
          words->push_back(candidate);
          if (wordBreakingHelper(s.substr(i, s.size()-i), dict, words))
            return true;
          words->pop_back();
        }
      }
      return false;
    }

  vector<string> WordBreaking(const string &s,
                              const unordered_set<string> &dict) {
    vector<string> words;
    wordBreakingHelper(s, dict, &words);
    return words;
  }

  vector<string> WordBreakingOptimized(const string &s,
                                       const unordered_set<string> &dict) {
    vector<int> splits(s.size()+1, -1);

    for (int i=1; i<=(int)s.size(); ++i) {
      string candidate(s.substr(0, i));
      if (dict.find(candidate) != dict.end())
        splits[i] = i;
      else {
        for (int j=0; j<i; ++j) {
          if (splits[j] != -1 &&
              dict.find(s.substr(j, i-j)) != dict.end()) {
            splits[i] = i-j;
            break;
          }
        }
      }
    }

    vector<string> words;
    if (splits.back() != -1) {
      for (int idx = s.size(); idx > 0; idx -= splits[idx])
        words.push_back(s.substr(idx-splits[idx], splits[idx]));
      reverse(words.begin(), words.end());
    }
    return words;
  }

  int FindMinimumTotal(vector<vector<int>> &triangle) {
    assert(!triangle.empty());
    vector<int> min_paths(triangle[triangle.size()-1].size());
    size_t idx = min_paths.size() - 1;
    
    min_paths[idx] = triangle[0][0];
    for (size_t i=1; i<triangle.size(); ++i) {
      min_paths[idx-1] = min_paths[idx] + triangle[i][0];
      for (size_t j=1; j<triangle[i].size(); ++j)
        min_paths[idx+(j-1)] = min_paths[idx+(j-1)] + triangle[i][j];
      --idx;
    }
    int min_path = numeric_limits<int>::max();
    for (auto len : min_paths) {
      if (len < min_path)
        min_path = len;
    }
    return min_path;
  }

  int pickUpCoinsHelper(const vector<int> &C, int a, int b,
                        vector<vector<int>> *T_ptr) {
    if (a > b)
      return 0;
    vector<vector<int>> &T = *T_ptr;
    if (T[a][b] == -1) {
      T[a][b] = max(C[a] + min(pickUpCoinsHelper(C, a+2, b, T_ptr),
                               pickUpCoinsHelper(C, a+1, b-1, T_ptr)),
                    C[b] + min(pickUpCoinsHelper(C, a, b-2, T_ptr),
                               pickUpCoinsHelper(C, a+1, b-1, T_ptr)));
    }
    return T[a][b];
  }

  int PickUpCoins(const vector<int> &C) {
    vector<vector<int>> T(C.size(), vector<int>(C.size(), -1));
    return pickUpCoinsHelper(C, 0, C.size()-1, &T);
  }

  int NumberOfSteps(int n, int k) {
    vector<int> steps(n+1);
    steps[0] = steps[1] = 1;
    for (int i=2; i<=n; ++i) {
      for (int j=1; j<=k && (i-j)>=0; ++j)
        steps[i] += steps[i-j];
    }
    return steps[n];
  }

  int NumberOfStepsOptimized(int n, int k) {
    vector<int> steps(k);
    steps[0] = steps[1] = 1;
    for (int i=2; i<=n; ++i) {
      vector<int> saved_steps(steps);
      steps[i%k] = 0;
      for (int j=1; j<=k && (i-j)>=0; ++j)
        steps[i%k] += saved_steps[(i-j)%k];
    }
    return steps[n%k];
  }

  double houseMajorityHelper(const vector<double> &prob, int r, int n,
                             vector<vector<double>> *P_ptr) {
    if (r < 0 || r > n)
      return 0.0;
    else if (r == 0 && n == 0)
      return 1.0;
    vector<vector<double>> &P = *P_ptr;
    if (P[r][n] == -1)
      P[r][n] = (houseMajorityHelper(prob, r-1, n-1, P_ptr) * prob[n-1]) +
        (houseMajorityHelper(prob, r, n-1, P_ptr) * (1.0 - prob[n-1]));
    return P[r][n];
  }

  double HouseMajority(const vector<double> &prob, int n) {
    double partial_sum {};
    vector<vector<double>> P(n+1, vector<double>(n+1, -1));
    assert(n&1);
    for (int r=(n/2)+1; r<=n; ++r)
      partial_sum += houseMajorityHelper(prob, r, n, &P);
    return partial_sum;
  }

  int FindPrettyPrinting(const vector<string> &W, int L, bool consider_last_line) {
    vector<long> M(W.size(), numeric_limits<long>::max());
    int b_len {};
    for (int i=0; i<(int)W.size(); ++i) {
      b_len = L - W[i].size();
      M[i] = min(((i<1) ? 0 : M[i-1]) + (1L << b_len), M[i]);
      assert(M[i] >= 0);
      for (int j=i-1; j>=0; --j) {
        b_len -= (W[j].size() + 1);
        if (b_len < 0)
          break;
        M[i] = min(((j<1) ? 0 : M[j-1]) + (1L << b_len), M[i]);
        assert(M[i] >= 0);
      }
    }

    long min_mess {};
    if (consider_last_line)
      min_mess = M[W.size()-1];
    else {
      min_mess = (W.size() >= (size_t)2) ? M[W.size() - 2] : 0;
      b_len = L - W.back().size();

      for (int i=W.size()-2; i>=0; --i) {
        b_len -= (W[i].size() + 1);
        if (b_len < 0)
          break;
        min_mess = min((i<1) ? 0 : M[i-1], min_mess);
      }
    }
    return min_mess;
  }

  vector<int> LongestNondecreasingSubsequence(const vector<int> &A) {
    int max_length_index {};
    vector<int> lengths(A.size(), 1);
    vector<int> previous_index(A.size(), -1);
    if (A.empty())
      return A;
    for (size_t i=1; i<A.size(); ++i) {
      for (size_t j=0; j<i; ++j) {
        if (A[j] < A[i] && (lengths[j]+1) > lengths[i]) {
          lengths[i] = lengths[j] + 1;
          previous_index[i] = j;
        }
      }
      if (lengths[i] > lengths[max_length_index])
        max_length_index = i;
    }
    int max_length = lengths[max_length_index];
    vector<int> sequence(max_length);
    while (max_length-- > 0) {
      sequence[max_length] = A[max_length_index];
      max_length_index = previous_index[max_length_index];
    }
    return sequence;
  }
}

