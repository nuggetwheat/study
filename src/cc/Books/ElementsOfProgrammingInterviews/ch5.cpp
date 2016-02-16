
#include "ch5.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <random>

extern "C" {
#include <math.h>
}

using namespace std;

namespace {
  std::default_random_engine dre;  
}

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

  long SwapBits(long x, int i, int j) {
    if (((x >> i) & 1) != ((x >> j) & 1)) {
      unsigned long mask = (1 << i) | (1 << j);
      x ^= mask;
    }
    return x;
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

  unsigned Add(unsigned a, unsigned b) {
    unsigned sum=0, carryin=0, k=1, temp_a=a, temp_b=b;
    while (temp_a || temp_b) {
      unsigned ak = a & k, bk = b & k;
      unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
      sum |= (ak ^ bk ^ carryin);
      carryin = carryout << 1;
      k <<= 1;
      temp_a >>= 1;
      temp_b >>= 1;
    }
    return sum | carryin;
  }

  unsigned Multiply(unsigned x, unsigned y) {
    unsigned product = 0;
    while (x) {
      if (x & 1)
        product = Add(product, y);
      x >>= 1;
      y <<= 1;
    }
    return product;
  }

  unsigned Divide(unsigned x, unsigned y) {
    unsigned quotient {};
    unsigned power = 32;
    unsigned long long y_power = static_cast<unsigned long long>(y) << power;
    while (x >= y) {
      while (y_power > x) {
        y_power >>= 1;
        --power;
      }
      x -= y_power;
      quotient |= (1 << power);
    }
    return quotient;
  }

  double Power(double x, int y) {
    double result {1.0};
    if (y < 0) {
      x = 1.0 / x;
      y *= -1;
    }
    while (y) {
      if (y & 1)
        result *= x;
      x *= x;
      y >>= 1;
    }
    return result;
  }

  long Reverse(int x) {
    long result {};
    bool is_negative = x < 0;
    x = x * (is_negative ? -1 : 1);
    while (x) {
      result = (result * 10) + (x % 10);
      x /= 10;
    }
    return is_negative ? -result : result;
  }

  bool IsPalindrome(int x) {
    if (x < 0)
      return false;
    else if (x == 0)
      return true;
    int msd = (unsigned)pow(10.0, floor(log10(x)));
    while (x) {
      if (x / msd != x % 10)
        return false;
      x %= msd;
      x /= 10;
      msd /= 100;
    }
    return true;
  }

  int ZeroOneRandom() {
    return std::uniform_int_distribution<int>(0, 1)(dre);
  }

  int UniformRandom(int lower_bound, int upper_bound) {
    int result;
    int target = upper_bound - lower_bound + 1;
    do {
      result = 0;
      for (int k = 1; k <= target; k <<= 1)
        result = (result << 1) + ZeroOneRandom();
    } while (result >= target);
    assert((result+lower_bound) >= lower_bound && (result+lower_bound) <= upper_bound);
    return result + lower_bound;
  }

}
