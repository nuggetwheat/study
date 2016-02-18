
#include "ch13.hpp"

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

namespace reference {

  vector<vector<string>> FindAnagrams(const vector<string> &dictionary) {
    unordered_map<string, vector<string>> anagrams;
    for (const auto &word : dictionary) {
      string word_sorted { word };
      sort(word_sorted.begin(), word_sorted.end());
      anagrams[word_sorted].push_back(word);
    }
    vector<vector<string>> result;    
    for (auto & elem : anagrams) {
      if (elem.second.size() > 1)
        result.push_back(elem.second);
    }
    return result;
  }

  bool CanFormPalindrome(const std::string &word) {
    unordered_map<char, int> counts;
    for (auto c : word)
      counts[c]++;
    int odd_count {};
    for (auto & entry : counts) {
      if (entry.second & 1) {
        if (++odd_count > 1)
          return false;
      }
    }
    return true;
  }

  study::BSTNode<int> *LCA_optimized(const std::unique_ptr<study::BSTNode<int>> &node0,
                                     const std::unique_ptr<study::BSTNode<int>> &node1) {
    auto *iter0 = node0.get(), *iter1 = node1.get();
    unordered_set<study::BSTNode<int> *> visited;
    while (iter0 || iter1) {
      if (iter0) {
        if (!visited.emplace(iter0).second)
          return iter0;
        iter0 = iter0->parent;
      }
      if (iter1) {
        if (!visited.emplace(iter1).second)
          return iter1;
        iter1 = iter1->parent;
      }
    }
    return nullptr;
  }

  int FindNearestRepetition(const std::vector<std::string> &paragraph) {
    unordered_map<string, size_t> positions;
    size_t nearest = numeric_limits<size_t>::max();
    for (size_t i=0; i<paragraph.size(); ++i) {
      auto iter = positions.find(paragraph[i]);
      if (iter != positions.end()) {
        size_t diff = i - iter->second;
        if (diff < nearest)
          nearest = diff;
      }
      positions[paragraph[i]] = i;
    }
    return nearest;
  }


}

