
#undef NDEBUG

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {
  char g_input[] = "ASORTINGEXAMPLE";
  char g_expected_output[] = "AAEEGILMNOPRSTX";

  void populate_input(vector<char> &buf) {
    buf.reserve(strlen(g_input)+1);
    for (auto i=0; g_input[i]; ++i)
      buf.push_back(g_input[i]);
    buf.push_back((char)0);
    buf.resize(strlen(g_input));
  }

  void verify_output(char *output) {
    if (strcmp(output, g_expected_output)) {
      cout << "   INPUT: " << g_input << "\n";
      cout << "  OUTPUT: " << output << "\n";
      cout << "EXPECTED: " << g_expected_output << "\n";
      cout << flush;
      exit(EXIT_FAILURE);
    }
  }
}

void mergesort(vector<char> &input, int begin, int end) {
  if (end-begin > 1) {
    int mid = (begin+end) / 2;
    mergesort(input, begin, mid);
    mergesort(input, mid, end);
    vector<char> buf(input.size());
    int i, j;
    for (i=mid-1; i>=begin; --i) {
      assert(input[i]);
      buf[i] = input[i];
    }
    i++;
    for (j=mid; j<end; ++j) {
      assert(input[j]);
      buf[(end-1)+mid-j] = input[j];
    }
    j--;
    for (auto k=begin; k<end; ++k) {
      if (buf[i] < buf[j]) {
        input[k] = buf[i];
        i++;
      }
      else {
        input[k] = buf[j];
        j--;
      }
    }
  }
}

int main(int argc, char **argv) {
  vector<char> input;

  populate_input(input);
  cout << "merge sort" << endl;
  mergesort(input, 0, input.size());
  verify_output(&input[0]);

  return 0;
}
