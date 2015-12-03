
#include <algorithm>
#include <iterator>

namespace study {

  template <typename ForwardIterator, typename UnaryPredicate>
  ForwardIterator partition(ForwardIterator beg, ForwardIterator end, UnaryPredicate pred) {
    while (beg != end && pred(*beg))
      ++beg;
    auto iter = beg;
    while (iter < end && !pred(*iter))
      ++iter;
    while (iter != end) {
      std::swap(*iter++, *beg++);
      while (beg != end && pred(*beg))
        ++beg;
      while (iter < end && !pred(*iter))
        ++iter;
    }
    return beg;
  }

  template <typename RandomAccessIterator>
  RandomAccessIterator qs_partition(RandomAccessIterator beg, RandomAccessIterator end) {
    auto iter = --end;
    // swap partition value into *iter
    if (beg < iter) {
      auto pv = *iter--;
      while (*beg < pv)
        ++beg;
      while (iter > beg && *iter > pv)
        --iter;
      while (beg < iter) {
        std::swap(*beg++, *iter--);
        while (*beg < pv)
          ++beg;
        while (iter > beg && *iter > pv)
          --iter;
      }
      if (beg != end)
        std::swap(*beg++, *end);
    }
    return beg;
  }
  

  template <typename RandomAccessIterator>
  void quicksort(RandomAccessIterator beg, RandomAccessIterator end) {
    if (beg < end-1) {
      auto iter = study::qs_partition(beg, end);
      quicksort(beg, iter);
      quicksort(iter, end);
    }
  }

  template <typename RandomAccessIterator>
  void nth_element(RandomAccessIterator beg, RandomAccessIterator nth, RandomAccessIterator end) {
    if (beg < end-1) {
      auto iter = qs_partition(beg, end);
      if (nth < iter)
        study::nth_element(beg, nth, iter);
      else
        study::nth_element(iter, nth, end);
    }
  }


}

#if 0

#undef NDEBUG

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

namespace {
  char g_input[] = "ASORTINGEXAMPLE";
  char g_expected_output[] = "AAEEGILMNOPRSTX";

  /** Partitions the input characters in the range input[begin..end)
   * @param input Input data
   * @param begin Beginning offset
   * @param end Ending offset (one past the end)
   * @return Partition <i>offset</i> such that all of the characters in the
   * range [begin..offset) are less than all of the characters in the range
   * [offset..end).
   */
  int partition(char *input, int begin, int end) {
    int i = begin-1;
    if (end > (begin+1)) {
      char v = input[end-1];
      int j = end;
      do {
        do { i++; } while (input[i] < v);
        do { j--; } while (input[j] > v);
        swap(input[i], input[j]);
      } while (j>i);
      swap(input[i], input[j]);
      swap(input[i], input[end-1]);
    }
    return i;
  }

  void populate_input(char *input, int *np) {
    *np = strlen(g_input);
    memcpy(input, g_input, *np);
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

void quick_sort(char *input, int begin, int end) {
  if (begin < end-1) {
    int i = partition(input, begin, end);
    quick_sort(input, begin, i);
    quick_sort(input, i, end);
  }
}


void select(char *input, int begin, int end, int k) {
  if (begin < end-1) {
    int i = partition(input, begin, end);
    if (begin+k < i)
      select(input, begin, i, k);
    else
      select(input, i, end, k-(i-begin));
  }
}


int main(int argc, char **argv) {
  char buf[16];
  char output[16];
  int n;

  populate_input(buf, &n);
  cout << "quick sort" << endl;
  quick_sort(buf, 0, n);
  verify_output(buf);

  cout << "select" << endl;
  for (int i=0; i<n; ++i) {
    populate_input(buf, &n);
    select(buf, 0, n, i);
    buf[n] = 0;
    output[i] = buf[i];
  }
  output[n] = 0;
  verify_output(output);  

  return 0;
}
#endif
