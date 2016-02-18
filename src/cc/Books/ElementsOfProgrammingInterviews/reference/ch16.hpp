
#ifndef Books_ElementsOfProgrammingInterviews_reference_ch16_hpp
#define Books_ElementsOfProgrammingInterviews_reference_ch16_hpp

#include "Common/Tree.hpp"

#include <array>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace reference {

  extern void MoveTowerOfHanoi(std::vector<std::stack<int>> &pegs, int to_peg);

  extern void MoveTowerOfHanoiIterative(std::vector<std::stack<int>> &pegs, int to_peg);

  extern std::vector<std::vector<int>> NQueens(int n);

  extern std::vector<std::vector<int>> NQueensIterative(int n);

  extern std::vector<std::vector<int>> Permutations(std::vector<int> A);

  extern std::vector<std::vector<int>> PermutationsIterative(std::vector<int> A);

  extern std::vector<std::vector<int>> GeneratePowerSet(const std::vector<int> &input);

  extern std::vector<std::vector<int>> GeneratePowerSetIterative(const std::vector<int> &input);

  extern std::vector<std::vector<int>> Combinations(int n, int k);

  extern std::vector<std::vector<int>> CombinationsIterative(int n, int k);

  extern std::vector<std::string> GenerateBalancedParenthesis(int num_pairs);

  extern std::vector<std::string> GenerateBalancedParenthesisIterative(int num_pairs);

  extern std::vector<std::vector<std::string>> PalindromePartitioning(const std::string &input);

  extern std::vector<std::unique_ptr<study::BSTNode<int>>> GenerateAllBinaryTrees(int num_nodes);

  extern bool SolveSudoku(std::vector<std::vector<int>> *partial_assignment);

  extern std::vector<int> GrayCode(int num_bits);

  extern std::vector<int> GrayCodeIterative(int num_bits);

  extern int ComputeDiameter(const std::unique_ptr<study::BSTNode<int>> &tree);

}

#endif // Books_ElementsOfProgrammingInterviews_reference_ch16_hpp
