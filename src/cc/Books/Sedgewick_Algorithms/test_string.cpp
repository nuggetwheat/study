
#undef NDEBUG

#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "string.hpp"

using namespace std;
using namespace study;

namespace {
  const string test_input("GTTATAGCTGATCGCGGCGTAGCGGCGAAGGCGATTTAGCGGCGTAAGTAGCGGCGATAGCGGCGAAGCGGCGAGCGGCGACGGCGAGGCGAGCGACGAGGTAGCGGCG");
  const string test_pattern("GTAGCGGCG");
  const vector<size_t> expected_matches { 18, 47, 100 };
}

namespace study {

  void test_string() {

    // Rabin-Karp
    {
      vector<size_t> matches;
      auto iter = rabin_karp_search(test_input.begin(), test_input.end(),
                                    test_pattern.begin(), test_pattern.end());
      while (iter != test_input.end()) {
        matches.push_back(iter-test_input.begin());
        iter = rabin_karp_search(++iter, test_input.end(),
                                 test_pattern.begin(), test_pattern.end());
      }
      assert(matches == expected_matches);
    }

  }

}
