
#include "ch16.hpp"
#include "reference/ch16.hpp"

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

  void MoveTowerOfHanoi(std::vector<std::stack<int>> &pegs, int to_peg) {
    reference::MoveTowerOfHanoi(pegs, to_peg);
  }

  void MoveTowerOfHanoiIterative(std::vector<std::stack<int>> &pegs, int to_peg) {
    reference::MoveTowerOfHanoiIterative(pegs, to_peg);
  }

  vector<vector<int>> NQueens(int n) {
    return reference::NQueens(n);
  }

  vector<vector<int>> NQueensIterative(int n) {
    return reference::NQueensIterative(n);
  }

  vector<vector<int>> Permutations(vector<int> A) {
    return reference::Permutations(A);
  }

  vector<vector<int>> PermutationsIterative(vector<int> A) {
    return reference::PermutationsIterative(A);
  }

  vector<vector<int>> GeneratePowerSet(const vector<int> &input) {
    return reference::GeneratePowerSet(input);
  }

  vector<vector<int>> GeneratePowerSetIterative(const vector<int> &input) {
    return reference::GeneratePowerSetIterative(input);
  }

  vector<vector<int>> Combinations(int n, int k) {
    return reference::Combinations(n, k);
  }

  vector<vector<int>> CombinationsIterative(int n, int k) {
    return reference::CombinationsIterative(n, k);
  }

  vector<string> GenerateBalancedParenthesis(int num_pairs) {
    return reference::GenerateBalancedParenthesis(num_pairs);
  }

  vector<string> GenerateBalancedParenthesisIterative(int num_pairs) {
    return reference::GenerateBalancedParenthesisIterative(num_pairs);
  }

  vector<vector<string>> PalindromePartitioning(const string &input) {
    return reference::PalindromePartitioning(input);
  }

  bool SolveSudoku(std::vector<std::vector<int>> *partial_assignment) {
    return reference::SolveSudoku(partial_assignment);
  }

  vector<int> GrayCode(int num_bits) {
    return reference::GrayCode(num_bits);
  }

  vector<int> GrayCodeIterative(int num_bits) {
    return reference::GrayCodeIterative(num_bits);
  }

  int ComputeDiameter(const std::unique_ptr<BSTNode<int>> &tree) {
    return reference::ComputeDiameter(tree);
  }

}

