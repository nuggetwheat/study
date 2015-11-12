
#include "bits.hpp"

size_t count_one_bits(unsigned int x) {
  size_t count {};
  unsigned int mask {1};
  size_t nbits = 8 * sizeof(x);
  for (size_t i=0; i<nbits; ++i) {
    if (x & mask)
      ++count;
    mask <<= 1;
  }
  return count;
}

size_t count_one_bits_strip_lowest(unsigned int x) {
  size_t count {};
  while (x) {
    ++count;
    x ^= x & ~(x-1);
  }
  return count;
}
