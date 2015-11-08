
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

namespace {
  char g_pattern[] = "10100111";
  char g_text[] = "0110010001010100111010100011101001110";
  char g_bm_pattern[] = "GTAGCGGCG";
  char g_bm_text[] =
    "GTTATAGCTGATCGCGGCGTAGCGGCGAAGGCGATTTAGCGGCGTAAGTAGCGGCGATAGCGGCGAAGCGGCGAGCGGCGACGGCGAGGCGAGCGACGAGGTAGCGGCG";
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


class BadCharRule {
public:
  BadCharRule(const char *pattern)
  : m_shifts(new map<char, int>[strlen(pattern)]) {
    map<char, int> lastoffset;
    for (auto i = 0; pattern[i]; ++i)
      lastoffset[pattern[i]] = -1;
    for (auto i = 0; pattern[i]; ++i) {
      for (auto &entry : lastoffset) {
        if (entry.first == pattern[i]) {
          m_shifts[i][entry.first] = 0;
          lastoffset[entry.first] = i;
        }
        else 
          m_shifts[i][entry.first] = i - lastoffset[entry.first];
      }
    }
  }
  int shift(int offset, char c) {
    auto iter = m_shifts[offset].find(c);
    if (iter == m_shifts[offset].end())
      return offset + 1;
    return iter->second;
  }
private:
  unique_ptr<map<char, int>[]> m_shifts;
};


class GoodSuffixRule {
public:
  GoodSuffixRule(const char *pattern) :
    m_plen(strlen(pattern)), m_shifts(new int[m_plen]) {
    assert(*pattern);
    int lastpos = m_plen - 1;
    m_shifts[lastpos] = 0;
    int i, j;
    for (j = lastpos-1; j>0; --j) {
      for (i=j-1; i>=0; --i) {
        if (!strncmp(&pattern[i], &pattern[j+1], lastpos-j)) {
          m_shifts[j] = j - i;
          break;
        }
      }
      if (i < 0)
        break;
    }
    while (j >= 0)
      m_shifts[j--] = 0;
  }
  int shift(int offset) {
    return m_shifts[offset];
  }
private:
  size_t m_plen {};
  unique_ptr<int[]> m_shifts;
};

bool advance_index(const char *text, int &i, int n) {
  for (auto j = 0; j<n; ++j) {
    if (text[i++] == 0)
      return false;
  }
  return true;
}

int bm_search(char *text, char *pattern, int start, BadCharRule &bcs, GoodSuffixRule &gss) {
  size_t plen = strlen(pattern);
  int i = start;
  int j = plen - 1;
  if (!advance_index(text, i, j))
    return -1;
  int shift, matching;
  while (true) {
    while (j > 0 && text[i] == pattern[j]) {
      j--;
      i--;
    }
    if (pattern[j] == text[i])
      return i;
    shift = max( bcs.shift(j, text[i]), gss.shift(j) );
    matching = (plen-1) - j;
    if (!advance_index(text, i, shift+matching))
      break;
    j = plen - 1;
  }
  return -1;
}


int main(int argc, char **argv) {
  int match;

  // Knuth-Morris-Pratt
  {
    vector<int> next;
    match = -1;
    cout << "[Knuth-Morris-Pratt]" << endl;
    while ((match = kmp_search(g_text, g_pattern, match+1)) != -1)
      cout << "match = " << match << endl;
  }

  // Boyer-Moore
  {
    BadCharRule bcs(g_bm_pattern);
    GoodSuffixRule gss(g_bm_pattern);
    match = -1;
    cout << "[Boyer-Moore]" << endl;
    while ((match = bm_search(g_bm_text, g_bm_pattern, match+1, bcs, gss)) > 0)
      cout << "match = " << match << endl;
  }

  return 0;
}
