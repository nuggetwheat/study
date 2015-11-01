
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
  char g_input[] = "AAEEGILMNOPRSTX";
}

int interpolation_search(char *input, int begin, int end, char v) {
  if (end-begin < 2) {
    if (end == begin || v != input[begin])
      return -1;
    return begin;
  }
  int x = (v - input[begin]) * (end-begin) / (input[end-1]-input[begin]);
  if (input[x] > v)
    return interpolation_search(input, begin, x, v);
  else if (input[x] < v)
    return interpolation_search(input, x, end, v);
  return x;
}

int main(int argc, char **argv) {

  cout << "interpolation search" << endl;
  cout << interpolation_search(g_input, 0, strlen(g_input), 'M') << endl;

  return 0;
}
