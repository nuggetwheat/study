
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "ch16.hpp"

using namespace std;
using namespace study;

namespace {

  void testMoveTowerOfHanoi() {
    cout << "[ch16] MoveTowerOfHanoi" << endl;
    vector<stack<int>> pegs(3);
    // recursive
    for (int i=6; i>=1; --i)
      pegs[0].push(i);
    MoveTowerOfHanoi(pegs, 2);
    for (int i=1; i<=6; ++i) {
      assert(pegs[2].top() == i);
      pegs[2].pop();
    }
    for (int i=7; i>=1; --i)
      pegs[0].push(i);
    MoveTowerOfHanoi(pegs, 1);
    for (int i=1; i<=7; ++i) {
      assert(pegs[1].top() == i);
      pegs[1].pop();
    }
    // iterative
    for (int i=6; i>=1; --i)
      pegs[0].push(i);
    MoveTowerOfHanoiIterative(pegs, 2);
    for (int i=1; i<=6; ++i) {
      assert(pegs[2].top() == i);
      pegs[2].pop();
    }
    for (int i=7; i>=1; --i)
      pegs[0].push(i);
    MoveTowerOfHanoiIterative(pegs, 1);
    for (int i=1; i<=7; ++i) {
      assert(pegs[1].top() == i);
      pegs[1].pop();
    }
  }

  void testNQueens() {
    cout << "[ch16] NQueens" << endl;
    vector<vector<int>> expected;
    expected.push_back({1,3,0,2});
    expected.push_back({2,0,3,1});
    auto result = NQueens(4);
    assert(result == expected);
    result = NQueensIterative(4);
    assert(result == expected);
  }

  void testPermutations() {
    cout << "[ch16] Permutations" << endl;
    vector<int> data {2, 3, 5, 7};
    vector<vector<int>> expected;
    expected.push_back({2,3,5,7});
    expected.push_back({2,3,7,5});
    expected.push_back({2,5,3,7});
    expected.push_back({2,5,7,3});
    expected.push_back({2,7,5,3});
    expected.push_back({2,7,3,5});
    expected.push_back({3,2,5,7});
    expected.push_back({3,2,7,5});
    expected.push_back({3,5,2,7});
    expected.push_back({3,5,7,2});
    expected.push_back({3,7,5,2});
    expected.push_back({3,7,2,5});
    expected.push_back({5,3,2,7});
    expected.push_back({5,3,7,2});
    expected.push_back({5,2,3,7});
    expected.push_back({5,2,7,3});
    expected.push_back({5,7,2,3});
    expected.push_back({5,7,3,2});
    expected.push_back({7,3,5,2});
    expected.push_back({7,3,2,5});
    expected.push_back({7,5,3,2});
    expected.push_back({7,5,2,3});
    expected.push_back({7,2,5,3});
    expected.push_back({7,2,3,5});
    auto result = Permutations(data);
    assert(result == expected);
    result = PermutationsIterative(data);
    assert(result == expected);
  }

  void testGeneratePowerSet() {
    cout << "[ch16] GeneratePowerSet" << endl;
    vector<vector<int>> expected;
    expected.push_back({});
    expected.push_back({3});
    expected.push_back({2});
    expected.push_back({2, 3});
    expected.push_back({1});
    expected.push_back({1, 3});
    expected.push_back({1, 2});
    expected.push_back({1, 2, 3});
    expected.push_back({0});
    expected.push_back({0, 3});
    expected.push_back({0, 2});
    expected.push_back({0, 2, 3});
    expected.push_back({0, 1});
    expected.push_back({0, 1, 3});
    expected.push_back({0, 1, 2});
    expected.push_back({0, 1, 2, 3});
    auto result = GeneratePowerSet({0, 1, 2, 3});
    assert(result == expected);
    result = GeneratePowerSetIterative({0, 1, 2, 3});
    assert(result == expected);
  }

  void testCombinations() {
    cout << "[ch16] Combinations" << endl;
    vector<vector<int>> expected;
    expected.push_back({1,2});
    expected.push_back({1,3});
    expected.push_back({1,4});
    expected.push_back({1,5});
    expected.push_back({2,3});
    expected.push_back({2,4});
    expected.push_back({2,5});
    expected.push_back({3,4});
    expected.push_back({3,5});
    expected.push_back({4,5});
    auto result = Combinations(5, 2);
    assert(result == expected);
    result = CombinationsIterative(5, 2);
    assert(result == expected);
#if 0
    for (auto & set : result) {
      cout << "{";
      for (auto & element : set)
        cout << element << ",";
      cout << "}" << endl;
    }
#endif
  }

  void testGenerateBalancedParenthesis() {
    cout << "[ch16] GenerateBalancedParenthesis" << endl;
    vector<string> expected;
    expected.push_back("((()))");
    expected.push_back("(()())");
    expected.push_back("(())()");
    expected.push_back("()(())");
    expected.push_back("()()()");
    auto result = GenerateBalancedParenthesis(3);
    assert(result == expected);
    result = GenerateBalancedParenthesisIterative(3);
    assert(result == expected);
  }

  void testPalindromePartitioning() {
    cout << "[ch16] PalindromePartitioning" << endl;
    vector<vector<string>> expected;
    expected.push_back({"0","2","0","4","4","5","1","8","8","1"});
    expected.push_back({"0","2","0","4","4","5","1","88","1"});
    expected.push_back({"0","2","0","4","4","5","1881"});
    expected.push_back({"0","2","0","44","5","1","8","8","1"});
    expected.push_back({"0","2","0","44","5","1","88","1"});
    expected.push_back({"0","2","0","44","5","1881"});
    expected.push_back({"020","4","4","5","1","8","8","1"});
    expected.push_back({"020","4","4","5","1","88","1"});
    expected.push_back({"020","4","4","5","1881"});
    expected.push_back({"020","44","5","1","8","8","1"});
    expected.push_back({"020","44","5","1","88","1"});
    expected.push_back({"020","44","5","1881"});
    auto result = PalindromePartitioning("0204451881");
    assert(result == expected);
#if 0
    for (auto & set : result) {
      cout << "{";
      for (auto & element : set)
        cout << "\"" << element << "\",";
      cout << "}" << endl;
    }
#endif
  }

  void testSolveSudoku() {
    cout << "[ch16] SolveSudoku" << endl;
    vector<vector<int>> input;
    input.push_back({0, 0, 0, 0, 8, 0, 0, 7, 9});
    input.push_back({0, 0, 0, 4, 1, 9, 0, 0, 5});
    input.push_back({0, 6, 0, 0, 0, 0, 2, 8, 0});
    input.push_back({7, 0, 0, 0, 2, 0, 0, 0, 6});
    input.push_back({4, 0, 0, 8, 0, 3, 0, 0, 1});
    input.push_back({8, 0, 0, 0, 6, 0, 0, 0, 3});
    input.push_back({0, 9, 8, 0, 0, 0, 0, 6, 0});
    input.push_back({6, 0, 0, 1, 9, 5, 0, 0, 0});
    input.push_back({5, 3, 0, 0, 7, 0, 0, 0, 0});
    vector<vector<int>> expected;
    expected.push_back({3,4,5,2,8,6,1,7,9});
    expected.push_back({2,8,7,4,1,9,6,3,5});
    expected.push_back({9,6,1,5,3,7,2,8,4});
    expected.push_back({7,1,3,9,2,4,8,5,6});
    expected.push_back({4,2,6,8,5,3,7,9,1});
    expected.push_back({8,5,9,7,6,1,4,2,3});
    expected.push_back({1,9,8,3,4,2,5,6,7});
    expected.push_back({6,7,2,1,9,5,3,4,8});
    expected.push_back({5,3,4,6,7,8,9,1,2});
    assert(SolveSudoku(&input));
    assert(input == expected);
  }

  void testGrayCode() {
    cout << "[ch16] GrayCode" << endl;
    auto result = GrayCode(3);
    vector<int> expected({0, 1, 3, 2, 6, 7, 5, 4});
    assert(result == expected);
    result = GrayCodeIterative(3);
    assert(result == expected);
  }

  void testComputeDiameter() {
    cout << "[ch16] ComputeDiameter" << endl;
    auto tree = buildTreeFigure10_1();
    assert(ComputeDiameter(tree) == 9);
    // add one level
    std::unique_ptr<BSTNode<int>> newTree(new BSTNode<int>());
    newTree->left.swap(tree);
    assert(ComputeDiameter(newTree) == 9);
  }
  
}


namespace study {

  void ch16_test() {
    testMoveTowerOfHanoi();
    testNQueens();
    testPermutations();
    testGeneratePowerSet();
    testCombinations();
    testGenerateBalancedParenthesis();
    testPalindromePartitioning();
    testSolveSudoku();
    testGrayCode();
    testComputeDiameter();
  }

}


