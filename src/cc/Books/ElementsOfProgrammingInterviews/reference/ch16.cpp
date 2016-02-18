
#include "ch16.hpp"

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

namespace reference {

  void moveTowerOfHanoiStep(int num_to_move,
                            std::vector<std::stack<int>> &pegs,
                            int from_peg, int to_peg, int use_peg) {
    if (num_to_move > 0) {
      moveTowerOfHanoiStep(num_to_move - 1, pegs, from_peg, use_peg, to_peg);
      assert(pegs[to_peg].empty() || pegs[to_peg].top() > pegs[from_peg].top());
      pegs[to_peg].push(pegs[from_peg].top());
      pegs[from_peg].pop();
      moveTowerOfHanoiStep(num_to_move - 1, pegs, use_peg, to_peg, from_peg);
    }
  }

  void MoveTowerOfHanoi(std::vector<std::stack<int>> &pegs, int to_peg) {
    assert(pegs.size() == 3);
    assert(!pegs[0].empty() && pegs[1].empty() && pegs[2].empty());
    assert(to_peg != 0 && to_peg < 3);
    int use_peg = to_peg == 2 ? 1 : 2;
    moveTowerOfHanoiStep(pegs[0].size(), pegs, 0, to_peg, use_peg);
  }

  struct hanoiState {
    hanoiState() { }
    hanoiState(int ntm, int f, int t, int u) : num_to_move(ntm), from_peg(f), to_peg(t), use_peg(u) { }
    void get(int *ntm, int *f, int *t, int *u) {
      *ntm = num_to_move;
      *f = from_peg;
      *t = to_peg;
      *u = use_peg;
    }
    int num_to_move {};
    int from_peg {};
    int to_peg {};
    int use_peg {};
  };

#if 0
  void moveTowerOfHanoiStepIterative(int num_to_move,
                                     std::vector<std::stack<int>> &pegs,
                                     int from_peg, int to_peg, int use_peg) {
    while (true) {
      if (num_to_move > 0) {
        moveTowerOfHanoiStepIterative(num_to_move - 1, pegs, from_peg, use_peg, to_peg);
        assert(pegs[to_peg].empty() || pegs[to_peg].top() > pegs[from_peg].top());
        pegs[to_peg].push(pegs[from_peg].top());
        pegs[from_peg].pop();
        swap(from_peg, use_peg);
        --num_to_move;
        continue;
      }
      break;
    }
  }
#endif

  void moveTowerOfHanoiStepIterative(int num_to_move,
                                     std::vector<std::stack<int>> &pegs,
                                     int from_peg, int to_peg, int use_peg) {
    stack<hanoiState> stateStack;
    while (true) {
      if (num_to_move == 0) {
        if (!stateStack.empty()) {
          stateStack.top().get(&num_to_move, &from_peg, &use_peg, &to_peg);
          stateStack.pop();
          goto label;
        }
        return;
      }
      stateStack.push(hanoiState(num_to_move, from_peg, use_peg, to_peg));
      --num_to_move;
      swap(use_peg, to_peg);
      continue;
    label:
      assert(pegs[to_peg].empty() || pegs[to_peg].top() > pegs[from_peg].top());
      pegs[to_peg].push(pegs[from_peg].top());
      pegs[from_peg].pop();
      // tail recursion
      --num_to_move;
      swap(from_peg, use_peg);
    }
  }

  void MoveTowerOfHanoiIterative(std::vector<std::stack<int>> &pegs, int to_peg) {
    assert(pegs.size() == 3);
    assert(!pegs[0].empty() && pegs[1].empty() && pegs[2].empty());
    assert(to_peg != 0 && to_peg < 3);
    int use_peg = to_peg == 2 ? 1 : 2;
    moveTowerOfHanoiStepIterative(pegs[0].size(), pegs, 0, to_peg, use_peg);
  }

  bool isValid(vector<int> &placement, int col) {
    for (int row=0; row<(int)placement.size(); ++row) {
      int colDiff = abs(col - placement[row]);
      if (colDiff == 0 || colDiff == (int)placement.size() - row)
        return false;
    }
    return true;
  }

  void SolveNQueens(int n, int row, vector<int> *placement, vector<vector<int>> *result) {
      if (row == n) {
        result->emplace_back(*placement);
      }
      else {
        for (int col=0; col<n; ++col) {
          if (isValid(*placement, col)) {
            placement->emplace_back(col);
            SolveNQueens(n, row+1, placement, result);
            placement->pop_back();
          }
        }
      }
  }

  vector<vector<int>> NQueens(int n) {
    vector<vector<int>> result;
    vector<int> placement;
    SolveNQueens(n, 0, &placement, &result);
    return result;
  }

  void SolveNQueensIterative(int n, int row, vector<int> *placement, vector<vector<int>> *result) {
    stack<pair<int,int>> stateStack;
    int col {};
    while (true) {
      if (row == n) {
        result->emplace_back(*placement);
        if (stateStack.empty())
          return;
        tie(row, col) = stateStack.top();
        stateStack.pop();
        goto label;
      }

      for (; col<n; ++col) {
        if (isValid(*placement, col)) {
          placement->emplace_back(col);
          stateStack.push({row, col});
          ++row;
          col = 0;
          break;
        label:
          placement->pop_back();
        }
      }
      if (col == n) {
        if (stateStack.empty())
          return;
        tie(row, col) = stateStack.top();
        stateStack.pop();
        goto label;
      }
    }
  }

  vector<vector<int>> NQueensIterative(int n) {
    vector<vector<int>> result;
    vector<int> placement;
    SolveNQueensIterative(n, 0, &placement, &result);
    return result;
  }

  void permutationsHelper(int row, vector<int> *A_ptr, vector<vector<int>> *result) {
    vector<int> &A = *A_ptr;
    if (row == (int)A.size() - 1) {
      result->emplace_back(A);
      return;
    }
    for (int i=row; i<(int)A.size(); ++i) {
      swap(A[row], A[i]);
      permutationsHelper(row+1, A_ptr, result);
      swap(A[row], A[i]);
    }
  }

  vector<vector<int>> Permutations(vector<int> A) {
    vector<vector<int>> result;
    if (!A.empty())
      permutationsHelper(0, &A, &result);
    return result;
  }

  void permutationsHelperIterative(int row, vector<int> *A_ptr, vector<vector<int>> *result) {
    stack<pair<int, int>> stateStack;
    vector<int> &A = *A_ptr;
    int i {};
    while (true) {
      if (row == (int)A.size() - 1) {
        result->emplace_back(A);
        if (!stateStack.empty()) {
          tie(row, i) = stateStack.top();
          stateStack.pop();
          goto label;
        }
        return;
      }
      i = row;
      for (; i<(int)A.size(); ++i) {
        swap(A[row], A[i]);
        stateStack.push({row, i});
        ++row;
        break;
      label:
        swap(A[row], A[i]);
      }
      if (i<(int)A.size())
        continue;
      if (!stateStack.empty()) {
        tie(row, i) = stateStack.top();
        stateStack.pop();
        goto label;
      }
      break;
    }
  }

  vector<vector<int>> PermutationsIterative(vector<int> A) {
    vector<vector<int>> result;
    if (!A.empty())
      permutationsHelperIterative(0, &A, &result);
    return result;
  }

  void generatePowerSetHelper(int position, const vector<int> &input,
                              vector<int> *subset, vector<vector<int>> *result) {
    if (position == (int)input.size()) {
      result->push_back(*subset);
      return;
    }
    for (int i=0; i<2; ++i) {
      if (i)
        subset->push_back(input[position]);
      generatePowerSetHelper(position+1, input, subset, result);
      if (i)
        subset->pop_back();
    }
  }

  vector<vector<int>> GeneratePowerSet(const vector<int> &input) {
    vector<vector<int>> result;
    vector<int> subset;
    generatePowerSetHelper(0, input, &subset, &result);
    return result;
  }

  void generatePowerSetHelperIterative(int position, const vector<int> &input,
                                       vector<int> *subset, vector<vector<int>> *result) {
    stack<pair<int, int>> stateStack;
    int work = 0x3;
    while (true) {
      if (position == (int)input.size()) {
        result->push_back(*subset);
        if (stateStack.empty())
          break;
        tie(work, position) = stateStack.top();
        stateStack.pop();
        if (work == 0)
          subset->pop_back();
      }
      if (work & 0x1) {
        stateStack.push({work ^ 0x1, position});
        ++position;
        work = 3;
        continue;
      }
      if (work & 0x2) {
        subset->push_back(input[position]);
        stateStack.push({0, position});
        ++position;
        work = 3;
        continue;
      }
      if (!stateStack.empty()) {
        tie(work, position) = stateStack.top();
        stateStack.pop();
        if (work == 0)
          subset->pop_back();
        continue;
      }
      break;
    }
  }

  vector<vector<int>> GeneratePowerSetIterative(const vector<int> &input) {
    vector<vector<int>> result;
    vector<int> subset;
    generatePowerSetHelperIterative(0, input, &subset, &result);
    return result;
  }

  void combinations(int n, int k, int offset, vector<int> *subset, vector<vector<int>> *result) {
    if (k == 0) {
      result->push_back(*subset);
      return;
    }
    for (int i=offset; i<=((n-k)+1); ++i) {
      assert(subset->empty() || subset->back() != i);
      subset->push_back(i);
      combinations(n, k-1, i+1, subset, result);
      subset->pop_back();
    }
  }

  vector<vector<int>> Combinations(int n, int k) {
    vector<vector<int>> result;
    vector<int> subset;
    combinations(n, k, 1, &subset, &result);
    return result;
  }

  void combinationsIterative(int n, int k, int offset, vector<int> *subset, vector<vector<int>> *result) {
    stack<tuple<int, int, int>> stateStack;
    int i{offset};
    while (true) {
      if (k == 0) {
        result->push_back(*subset);
        if (stateStack.empty())
          return;
        tie(i, k, offset) = stateStack.top();
        stateStack.pop();
        subset->pop_back();
      }
      for (; i<=((n-k)+1); ++i) {
        assert(subset->empty() || subset->back() != i);
        subset->push_back(i);
        stateStack.push(make_tuple(++i, k--, offset));
        offset = i;
        break;
      }
      if ((i-1) <= (n-k))
        continue;
      if (!stateStack.empty()) {
        tie(i, k, offset) = stateStack.top();
        stateStack.pop();
        subset->pop_back();
        continue;
      }
      break;
    }
  }

  vector<vector<int>> CombinationsIterative(int n, int k) {
    vector<vector<int>> result;
    vector<int> subset;
    combinationsIterative(n, k, 1, &subset, &result);
    return result;
  }

  void generateBalancedParenthesis(int num_pairs, int num_open, string *arrangement, vector<string> *result) {
    if (num_pairs == 0) {
      result->push_back(*arrangement);
      return;
    }
    // open paren
    if (num_open < num_pairs) {
      arrangement->push_back('(');
      generateBalancedParenthesis(num_pairs, num_open+1, arrangement, result);
      arrangement->pop_back();
    }
    // close paren
    if (num_open > 0) {
      arrangement->push_back(')');
      generateBalancedParenthesis(num_pairs-1, num_open-1, arrangement, result);
      arrangement->pop_back();
    }
  }

  vector<string> GenerateBalancedParenthesis(int num_pairs) {
    vector<string> result;
    string arrangement;
    generateBalancedParenthesis(num_pairs, 0, &arrangement, &result);
    return result;
  }

  void generateBalancedParenthesisIterative(int num_pairs, int num_open, string *arrangement, vector<string> *result) {
    stack<tuple<int, int, int>> frames;
    while (true) {
      if (num_pairs == 0) {
        result->push_back(*arrangement);
        if (frames.empty())
          return;
        int cont;
        tie(cont, num_pairs, num_open) = frames.top();
        frames.pop();
        if (cont)
          goto label1;
        goto label0;
      }
      // open paren
      if (num_open < num_pairs) {
        arrangement->push_back('(');
        frames.push(make_tuple(0, num_pairs, num_open++));
        continue;
      label0:
        arrangement->pop_back();
      }
      // close paren
      if (num_open > 0) {
        arrangement->push_back(')');
        frames.push(make_tuple(1, num_pairs--, num_open--));
        continue;
      label1:
        arrangement->pop_back();
      }
      if (frames.empty())
        return;
      int cont;
      tie(cont, num_pairs, num_open) = frames.top();
      frames.pop();
      if (cont)
        goto label1;
      goto label0;
    }
  }

  vector<string> GenerateBalancedParenthesisIterative(int num_pairs) {
    vector<string> result;
    string arrangement;
    generateBalancedParenthesisIterative(num_pairs, 0, &arrangement, &result);
    return result;
  }

  void palindromePartitioning(const string &input, vector<string> *current, vector<vector<string>> *result) {
    const char *front, *back;
    if (input.empty()) {
      result->push_back(*current);
      return;
    }
    for (size_t i=0; i<input.size(); ++i) {
      front = &input[0];
      back = &input[i];
      while (front < back && *front == *back) {
        ++front;
        --back;
      }
      if (front >= back) {
        current->push_back(input.substr(0, i+1));
        palindromePartitioning(input.substr(i+1), current, result);
        current->pop_back();
      }
    }
  }

  vector<vector<string>> PalindromePartitioning(const string &input) {
    vector<vector<string>> result;
    vector<string> current;
    palindromePartitioning(input, &current, &result);
    return result;
  }

#if 0
  vector<unique_ptr<study::BSTNode<int>>> GenerateAllBinaryTrees(int num_nodes) {
    vector<unique_ptr<study::BSTNode<int>>> result;
    if (num_nodes == 0)
      result.emplace_back(nullptr);

    for (int left_nodes=0; left_nodes<num_nodes; ++left_nodes) {
      int right_nodes = (num_nodes-1) - left_nodes;
      auto left_trees = GenerateAllBinaryTrees(left_nodes);
      auto right_trees = GenerateAllBinaryTrees(right_nodes);
      for (auto & ltree : left_trees) {
        for (auto & rtree : right_trees) {
          unique_ptr<study::BSTNode<int>> tree(new study::BSTNode<int>(0));
          tree->left.swap(ltree);
          tree->right.swap(rtree);
          result.emplace_back(tree);
        }
      }
    }
    return result;
  }
#endif

  bool validAddSudoku(const std::vector<std::vector<int>> &partial_assignment,
                      int i, int j, int val) {
    // row
    for (int idx=0; idx<(int)partial_assignment.size(); ++idx) {
      if (partial_assignment[i][idx] == val)
        return false;
    }

    // column
    for (int idx=0; idx<(int)partial_assignment.size(); ++idx) {
      if (partial_assignment[idx][j] == val)
        return false;
    }

    // grid
    int grid_size = sqrt(partial_assignment.size());
    int grid_start_row = (i / grid_size) * grid_size;
    int grid_start_col = (j / grid_size) * grid_size;
    for (int gi=grid_start_row; gi<(grid_start_row+grid_size); ++gi) {
      for (int gj=grid_start_col; gj<(grid_start_col+grid_size); ++gj) {
        if (partial_assignment[gi][gj] == val)
          return false;
      }
    }
      
    return true;
  }

  bool solvePartialSudoku(size_t i, size_t j, std::vector<std::vector<int>> *partial_assignment) {
    if (i == partial_assignment->size()) {
      i = 0;
      if (++j == (*partial_assignment)[i].size())
        return true;
    }
    if ((*partial_assignment)[i][j] != 0)
      return solvePartialSudoku(i+1, j, partial_assignment);

    for (int val = 1; val <= (int)partial_assignment->size(); ++val) {
      if (validAddSudoku(*partial_assignment, i, j, val)) {
        (*partial_assignment)[i][j] = val;
        if (solvePartialSudoku(i+1, j, partial_assignment))
          return true;
      }      
    }
    (*partial_assignment)[i][j] = 0;
    return false;
  }

  bool SolveSudoku(std::vector<std::vector<int>> *partial_assignment) {
    return solvePartialSudoku(0, 0, partial_assignment);
  }

  bool differByOneBit(int x, int y) {
    int val = x ^ y;
    return val && (val & (val-1)) == 0;
  }

  bool grayCodeHelper(int num_bits, vector<int> *result, unordered_set<int> *history) {

    if (result->size() == (size_t)(1 << num_bits))
      return differByOneBit(result->front(), result->back());

    for (int i=0; i<num_bits; ++i) {
      int candidate = result->back() ^ (1 << i);
      if (history->count(candidate) == 0 && differByOneBit(result->back(), candidate)) {
        history->emplace(candidate);
        result->emplace_back(candidate);
        if (grayCodeHelper(num_bits, result, history))
          return true;
        result->pop_back();
        history->erase(candidate);
      }
    }
    return false;
  }

  vector<int> GrayCode(int num_bits) {
    vector<int> result;
    unordered_set<int> history;
    result.emplace_back(0);
    history.emplace(0);
    grayCodeHelper(num_bits, &result, &history);
    return result;
  }

  void grayCodeHelperIterative(int num_bits, vector<int> *result, unordered_set<int> *history) {
    stack<pair<int, int>> stateStack;
    int i {};
    int candidate {};

    while (true) {

      if (result->size() == (size_t)(1 << num_bits)) {
        if (differByOneBit(result->front(), result->back()))
          return;
        assert(!stateStack.empty());
        tie(i, candidate) = stateStack.top();
        stateStack.pop();
        goto label;
      }

      i = 0;
      for (; i<num_bits; ++i) {
        candidate = result->back() ^ (1 << i);
        if (history->count(candidate) == 0 && differByOneBit(result->back(), candidate)) {
          history->emplace(candidate);
          result->emplace_back(candidate);
          stateStack.push({i, candidate});
          break;
        label:
          //if (grayCodeHelperIterative(num_bits, result, history))
          //return true;
          result->pop_back();
          history->erase(candidate);
        }
      }
      if (i<num_bits)
        continue;
      assert(!stateStack.empty());
      tie(i, candidate) = stateStack.top();
      stateStack.pop();
      goto label;
    }
  }

  vector<int> GrayCodeIterative(int num_bits) {
    vector<int> result;
    unordered_set<int> history;
    result.emplace_back(0);
    history.emplace(0);
    grayCodeHelperIterative(num_bits, &result, &history);
    return result;
  }

  pair<int, int> computeDiameterHelper(const std::unique_ptr<study::BSTNode<int>> &node) {
    if (!node->left && !node->right)
      return {0, 0};
    int left_height {-1};
    int right_height {-1};
    pair<int, int> left {0, 0};
    pair<int, int> right {0, 0};
    if (node->left) {
      left = computeDiameterHelper(node->left);
      left_height = left.first;
    }
    if (node->right) {
      right = computeDiameterHelper(node->right);
      right_height = right.first;
    }
    int new_diameter = (left_height+1) + (right_height+1);
    return {max(left_height, right_height)+1, max(new_diameter, max(left.second, right.second))};
  }

  int ComputeDiameter(const std::unique_ptr<study::BSTNode<int>> &tree) {
    return tree ? computeDiameterHelper(tree).second : 0;
  }

}

