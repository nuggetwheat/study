
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

#include "ch13.hpp"

using namespace std;
using namespace study;

namespace {

  void testFindAnagrams() {
    cout << "[ch13] FindAnagrams" << endl;
    vector<string> dictionary {"debitcard", "elvis", "silent", "badcredit",
                               "lives", "freedom", "listen", "levis", "money"};
    vector<vector<string>> expected;
    expected.push_back({"elvis", "lives", "levis"});
    expected.push_back({"debitcard", "badcredit"});
    expected.push_back({"silent", "listen"});
    auto result = FindAnagrams(dictionary);
    assert(result == expected);
  }

  void testCanFormPalindrome() {
    cout << "[ch13] CanFormPalindrome" << endl;
    assert(CanFormPalindrome("edified"));
    assert(CanFormPalindrome("a man a plan a canal panama"));
    assert(!CanFormPalindrome("Monster"));
  }

  void testLCA_optimized() {
    cout << "[ch13] LCA_optimized" << endl;
    std::unique_ptr<BSTNode<int>> tree = buildTreeFigure10_1(true);
    auto ancester = LCA_optimized(tree->right->left->right->left->right,
                                  tree->right->right->right);
    assert(ancester->data == 6);
  }

  void testFindNearestRepetition() {
    cout << "[ch13] FindNearestRepetition" << endl;
    vector<string> paragraph = { "All", "work", "and", "no", "play", "make",
                                 "for", "no", "work", "no", "fun", "and", "no",
                                 "results" };
    assert(FindNearestRepetition(paragraph) == 2);
  }
  
}


namespace study {

  void ch13_test() {
    testFindAnagrams();
    testCanFormPalindrome();
    testLCA_optimized();
    testFindNearestRepetition();
  }

}


