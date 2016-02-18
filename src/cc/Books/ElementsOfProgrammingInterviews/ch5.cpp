
#include "ch5.hpp"
#include "reference/ch5.hpp"

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
    return reference::CountOneBitsBruteForce(x);
  }

  size_t CountOneBitsStripLowest(unsigned int x) {
    return reference::CountOneBitsStripLowest(x);
  }

  short ParityBruteForce(unsigned int x) {
    return reference::ParityBruteForce(x);
  }

  short ParityStripLowest(unsigned int x) {
    return reference::ParityStripLowest(x);
  }

  long SwapBits(long x, int i, int j) {
    return reference::SwapBits(x, i, j);
  }

  unsigned long ClosestIntSameBitCount(unsigned long x) {
    return reference::ClosestIntSameBitCount(x);
  }

  unsigned long ClosestIntSameBitCount2(unsigned long x) {
    return reference::ClosestIntSameBitCount2(x);
  }

  unsigned Add(unsigned a, unsigned b) {
    return reference::Add(a, b);
  }

  unsigned Multiply(unsigned x, unsigned y) {
    return reference::Multiply(x, y);
  }

  unsigned Divide(unsigned x, unsigned y) {
    return reference::Divide(x, y);
  }

  double Power(double x, int y) {
    return reference::Power(x, y);
  }

  long Reverse(int x) {
    return reference::Reverse(x);
  }

  bool IsPalindrome(int x) {
    return reference::IsPalindrome(x);
  }

  int UniformRandom(int lower_bound, int upper_bound) {
    return reference::UniformRandom(lower_bound, upper_bound);
  }

}
