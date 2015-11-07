
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
  char g_pattern[] = "10100111";
  char g_text[] = "0110010001010100111010100011101001110";
}

void kmp_fill_next_array(const char *pattern, vector<int> &next) {
  next.resize(strlen(pattern));
  int i = 0;
  int j = -1;
  next[0] = -1;
  do {
    if (j == -1 || pattern[i] == pattern[j])
      next[++i] = ++j;
    else
      j = next[j];
  } while (i < next.size());
}


int kmp_search(char *text, char *pattern, int start) {
  vector<int> next;
  kmp_fill_next_array(pattern, next);
  int text_len = strlen(text);
  int i = start;
  int j {0};
  do {
    if (j == -1 || text[i] == pattern[j]) {
      ++i;
      ++j;
    }
    else
      j = next[j];
  } while (j < (int)next.size() && i < text_len);
  if (j == next.size())
    return i - next.size();
  return -1;
}

int main(int argc, char **argv) {
  vector<int> next;

  int ret = -1;

  while ((ret = kmp_search(g_text, g_pattern, ret+1)) != -1)
    cout << "Match at position " << ret << endl;

  return 0;
}
