
#include "ch13.hpp"
#include "reference/ch13.hpp"

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
#include <unordered_set>
#include <utility>
#include <vector>

extern "C" {
#include <math.h>
}

using namespace std;

namespace study {

  vector<vector<string>> FindAnagrams(const vector<string> &dictionary) {
    return reference::FindAnagrams(dictionary);
  }

  bool CanFormPalindrome(const std::string &word) {
    return reference::CanFormPalindrome(word);
  }

  BSTNode<int> *LCA_optimized(const std::unique_ptr<BSTNode<int>> &node0,
                              const std::unique_ptr<BSTNode<int>> &node1) {
    return reference::LCA_optimized(node0, node1);
  }

  int FindNearestRepetition(const std::vector<std::string> &paragraph) {
    return reference::FindNearestRepetition(paragraph);
  }

}

