
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

namespace study {

template <typename T>
void validate_partition(T *input, size_t begin, size_t end, size_t p) {
  if (p > begin && p < end) {
    auto lower_max_iter = std::max_element(&input[begin], &input[p]);
    auto upper_min_iter = std::min_element(&input[p], &input[end]);
    assert(*lower_max_iter <= *upper_min_iter);
  }
}


/** Partitions the input in the range input[begin..end)
 * @param input Input data
 * @param begin Beginning offset
 * @param end Ending offset (one past the end)
 * @return Partition <i>offset</i> such that all of the elements in the
 * range [begin..offset) are less than all of the elements in the range
 * [offset..end).
 */
template <typename T>
size_t partition(T *input, size_t begin, size_t end) {
  size_t i = begin;
  if (begin < end) {
    T v = input[end-1];
    size_t j = end - 1;
    while (i<end && input[i]<v)
      ++i;
    while (j>i && input[j]>v)
      --j;
    while (i<j) {
      std::swap(input[i++], input[j--]);
      while (i<end && input[i]<v)
        ++i;
      while (j>i && input[j]>v)
        --j;
    }
  }
  validate_partition(input, begin, end, i);
  return i;
}


template <typename T>
T nth_element(T *input, size_t begin, size_t end, size_t i) {
  if (begin+1 == end) {
    assert(i == 0);
    return input[begin];
  }
  auto p = partition(input, begin, end);
  auto prel = p - begin;
  if (i < prel)
    return nth_element(input, begin, p, i);
  return nth_element(input, p, end, i-prel);
}

}
