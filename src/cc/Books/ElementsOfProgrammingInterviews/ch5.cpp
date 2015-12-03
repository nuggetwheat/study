
#include <stdexcept>

#include "ch5.hpp"

namespace study {

  size_t CountOneBitsBruteForce(unsigned int x) {
    size_t count {};
    while (x) {
      if (x & 1)
        ++count;
      x >>= 1;
    }
    return count;
  }

  size_t CountOneBitsStripLowest(unsigned int x) {
    size_t count {};
    while (x) {
      x &= (x-1);
      ++count;
    }
    return count;
  }

  short ParityBruteForce(unsigned int x) {
    short result = 0;
    while (x) {
      if (x & 1)
        ++result;
      x >>= 1;
    }
    return result % 2;
  }

  short ParityStripLowest(unsigned int x) {
    short result = 0;
    while (x) {
      result ^= 1;
      x &= (x-1);
    }
    return result;
  }

  unsigned long ClosestIntSameBitCount(unsigned long x) {
    for (int i=0; i<63; ++i) {
      if (((x >> i) & 1) != ((x >> (i + 1)) & 1)) {
        x ^= (1UL << i) | (1UL << (i + 1));  // swap bit (i) and bit (i+1)
        return x;
      }
    }
    throw std::invalid_argument("all bits are 0 or 1");
  }

  unsigned long ClosestIntSameBitCount2(unsigned long x) {
    unsigned long mask = 3;
    for (int i=0; i<62; ++i) {
      if ((x & mask) && (x & mask) != mask) {
        x ^= mask;
        return x;
      }
      mask <<= 1;
    }
    throw std::invalid_argument("all bits are 0 or 1");
  }

}


