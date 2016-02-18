
#include "ch17.hpp"
#include "reference/ch17.hpp"

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

namespace study {

  size_t FibonacciRecursive(size_t nth) {
    return reference::FibonacciRecursive(nth);
  }

  size_t FibonacciDynamic(size_t nth) {
    return reference::FibonacciDynamic(nth);
  }

  pair<int, int> FindMaximumSubarray(const vector<int> &A) {
    return reference::FindMaximumSubarray(A);
  }

  int CountCombinations(int total_score, const vector<int> &ways) {
    return reference::CountCombinations(total_score, ways);
  }

  int CountPermutations(int total_score, const vector<int> &ways) {
    return reference::CountPermutations(total_score, ways);
  }

  int EditDistance(const string &A, const string &B) {
    return reference::EditDistance(A, B);
  }

  int EditDistanceOptimized(string A, string B) {
    return reference::EditDistanceOptimized(A, B);
  }

  int MinimumRemovalsToPalindrome(string str) {
    return reference::MinimumRemovalsToPalindrome(str);
  }

  int NumberOfWaysToTraverse2DArray(int n, int m) {
    return reference::NumberOfWaysToTraverse2DArray(n, m);
  }

  int NumberOfWaysToTraverse2DArrayOptimized(int n, int m) {
    return reference::NumberOfWaysToTraverse2DArrayOptimized(n, m);
  }

  int CountMonotone(int k) {
    return reference::CountMonotone(k);
  }

  int CountMonotoneOptimized(int k) {
    return reference::CountMonotoneOptimized(k);
  }

  int MaximizeFishing(std::vector<std::vector<int>> &sea) {
    return reference::MaximizeFishing(sea);
  }

  bool Match(const vector<vector<int>> &A, const vector<int> &S) {
    return reference::Match(A, S);
  }

  int Knapsack(int capacity, const vector<reference::Item> &items) {
    return reference::Knapsack(capacity, items);
  }

  int KnapsackOptimized(int capacity, const std::vector<reference::Item> &items) {
    return reference::KnapsackOptimized(capacity, items);
  }

  int MinimizeDifference(const std::vector<int> &A) {
    return reference::MinimizeDifference(A);
  }

  vector<string> WordBreaking(const string &s,
                              const unordered_set<string> &dict) {
    return reference::WordBreaking(s, dict);
  }

  vector<string> WordBreakingOptimized(const string &s,
                                       const unordered_set<string> &dict) {
    return reference::WordBreakingOptimized(s, dict);
  }

  int FindMinimumTotal(vector<vector<int>> &triangle) {
    return reference::FindMinimumTotal(triangle);
  }

  int PickUpCoins(const vector<int> &C) {
    return reference::PickUpCoins(C);
  }

  int NumberOfSteps(int n, int k) {
    return reference::NumberOfSteps(n, k);
  }

  int NumberOfStepsOptimized(int n, int k) {
    return reference::NumberOfStepsOptimized(n, k);
  }

  double HouseMajority(const vector<double> &prob, int n) {
    return reference::HouseMajority(prob, n);
  }

  int FindPrettyPrinting(const vector<string> &W, int L, bool consider_last_line) {
    return reference::FindPrettyPrinting(W, L, consider_last_line);
  }

  vector<int> LongestNondecreasingSubsequence(const vector<int> &A) {
    return reference::LongestNondecreasingSubsequence(A);
  }
}

