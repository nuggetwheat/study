
#ifndef Books_ElementsOfProgrammingInterviews_ch17_hpp
#define Books_ElementsOfProgrammingInterviews_ch17_hpp

#include "Common/Tree.hpp"

#include <array>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

namespace study {

  extern size_t FibonacciRecursive(size_t nth);

  extern size_t FibonacciDynamic(size_t nth);

  extern std::pair<int, int> FindMaximumSubarray(const std::vector<int> &A);

  extern int CountCombinations(int score, const std::vector<int> &ways);

  extern int CountPermutations(int score, const std::vector<int> &ways);

  extern int EditDistance(const std::string &A, const std::string &B);

  extern int EditDistanceOptimized(std::string A, std::string B);

  extern int MinimumRemovalsToPalindrome(std::string str);

  extern int NumberOfWaysToTraverse2DArray(int n, int m);

  extern int NumberOfWaysToTraverse2DArrayOptimized(int n, int m);

  extern int CountMonotone(int k);

  extern int CountMonotoneOptimized(int k);

  extern int MaximizeFishing(std::vector<std::vector<int>> &sea);

  extern bool Match(const std::vector<std::vector<int>> &A, const std::vector<int> &S);

  struct Item {
    int value, weight;
  };

  extern int Knapsack(int capacity, const std::vector<Item> &items);

  extern int KnapsackOptimized(int capacity, const std::vector<Item> &items);

  extern int MinimizeDifference(const std::vector<int> &A);

  extern std::vector<std::string> WordBreaking(const std::string &s,
                                               const std::unordered_set<std::string> &dict);

  extern std::vector<std::string> WordBreakingOptimized(const std::string &s,
                                                        const std::unordered_set<std::string> &dict);

  extern int FindMinimumTotal(std::vector<std::vector<int>> &triangle);

  extern int PickUpCoins(const std::vector<int> &C);

  extern int NumberOfSteps(int n, int k);

  extern int NumberOfStepsOptimized(int n, int k);

  extern double HouseMajority(const std::vector<double> &prob, int n);

  extern int FindPrettyPrinting(const std::vector<std::string> &W, int L, bool consider_last_line);

  extern std::vector<int> LongestNondecreasingSubsequence(const std::vector<int> &A);

}

#endif // Books_ElementsOfProgrammingInterviews_ch17_hpp
