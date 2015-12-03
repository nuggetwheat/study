
#undef NDEBUG

#include <cassert>
#include <functional>
#include <iostream>
#include <random>

#include "ch5.hpp"

using namespace std;
using namespace study;

namespace {

  default_random_engine g_re(42);
  uniform_int_distribution<unsigned int> g_dist;

  void testCountOneBits() {
    cout << "[ch5] CountOneBits" << endl;
    auto rng = bind(g_dist, g_re);
    unsigned int num;
    for (size_t i=0; i<1000; ++i) {
      num = rng();
      assert(CountOneBitsBruteForce(num) == CountOneBitsStripLowest(num));
    }
  }

  void testParity() {
    cout << "[ch5] Parity" << endl;
    auto rng = bind(g_dist, g_re);
    unsigned int num;
    for (size_t i=0; i<1000; ++i) {
      num = rng();
      assert(ParityBruteForce(num) == ParityStripLowest(num));
    }
  }

  void testClosestIntSameBitCount() {
    cout << "[ch5] ClosestIntSameBitCount" << endl;
    auto rng = bind(g_dist, g_re);
    unsigned int num;
    for (size_t i=0; i<1000; ++i) {
      num = rng();
      assert(ClosestIntSameBitCount(num) == ClosestIntSameBitCount2(num));
    }
  }

}

namespace study {

  void ch5_test() {
    testCountOneBits();
    testParity();
    testClosestIntSameBitCount();
  }

}


