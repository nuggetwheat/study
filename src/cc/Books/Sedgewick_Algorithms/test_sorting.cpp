
#undef NDEBUG

#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "quicksort.hpp"

using namespace std;
using namespace study;

namespace {

  const initializer_list<char> test_input {
    'A', 'S', 'O', 'R', 'T', 'I', 'N', 'G', 'E', 'X', 'A', 'M', 'P', 'L', 'E'
  };

  const vector<char> expected_output {
    'A', 'A', 'E', 'E', 'G', 'I', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'X'
  };

}

namespace study {

  void test_sorting() {

    // partition
    {
      vector<char> data(test_input);
      auto iter = study::partition(data.begin(), data.end(),
                                   [](char c){ return c < 'M'; });
      for_each(data.begin(), iter, [](char c){ assert(c < 'M'); });
      for_each(iter, data.end(), [](char c){ assert(c >= 'M'); });
    }

    // quicksort
    {
      vector<char> data(test_input);
      quicksort(data.begin(), data.end());
      assert(data == expected_output);
    }

    // nth_element
    {
      vector<char> output;
      output.reserve(expected_output.size());
      for (size_t i=0; i<test_input.size(); ++i) {
        vector<char> data(test_input);
        auto iter = data.begin() + i;
        study::nth_element(data.begin(), iter, data.end());
        output.push_back(*iter);
      }
      assert(output == expected_output);
    }

  }

}
