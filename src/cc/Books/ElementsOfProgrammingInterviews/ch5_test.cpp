
#undef NDEBUG

#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <math.h>
#include <random>
#include <sstream>

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

  void testSwapBits() {
    cout << "[ch5] SwapBits" << endl;
    assert(SwapBits(73, 1, 6) == 11);
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

  void testArithmetic() {
    cout << "[ch5] Arithmetic" << endl;
    uniform_int_distribution<unsigned> dist(0, 1000000000);
    for (size_t i=0; i<1000; ++i) {
      unsigned a = dist(g_re);
      unsigned b = dist(g_re);
      assert(Add(a,b) == (a+b));
    }
    uniform_int_distribution<unsigned> dist2(0, 65535);
    for (size_t i=0; i<1000; ++i) {
      unsigned a = dist2(g_re);
      unsigned b = dist2(g_re);
      assert(Multiply(a,b) == (a*b));
    }
    for (size_t i=0; i<1000; ++i) {
      unsigned x = dist(g_re);
      unsigned y = dist(g_re);
      if (x > y)
        assert(Divide(x, y) == x/y);
      else
        assert(Divide(y, x) == y/x);
    }
    uniform_real_distribution<double> rdist(0.0, 1000000000.0);
    uniform_int_distribution<int> dist3(-10, 10);
    for (size_t i=0; i<1000; ++i) {
      double x = rdist(g_re);
      int y = dist3(g_re);
      stringstream a, b;
      a << Power(x, y);
      b << pow(x, (double)y);
      assert(a.str() == b.str());
    }    

  }

  void testReverse() {
    cout << "[ch5] Reverse" << endl;
    assert(Reverse(123) == 321L);
    assert(Reverse(72993) == 39927L);
    assert(Reverse(-18) == -81L);
    assert(Reverse(-823774) == -477328L);
    assert(Reverse(72720183) == 38102727L);
  }

  void testIsPalindrome() {
    cout << "[ch5] IsPalindrome" << endl;
    assert(IsPalindrome(0));
    assert(IsPalindrome(1));
    assert(IsPalindrome(7));
    assert(IsPalindrome(11));
    assert(IsPalindrome(121));
    assert(IsPalindrome(333));
    assert(IsPalindrome(2147447412));
    assert(!IsPalindrome(-1));
    assert(!IsPalindrome(12));
    assert(!IsPalindrome(100));
    assert(!IsPalindrome(2147483647));
  }

  void testUniformRandom() {
    cout << "[ch5] UniformRandom" << endl;
    int val[6];
    memset(val, 0, 6*sizeof(int));
    for (size_t i=0; i<1000000; ++i)
      val[UniformRandom(5,10)-5]++;
    double mean {};
    for (int i=0; i<6; ++i)
      mean += val[i];
    mean /= 6.0;
    double variance {};
    for (int i=0; i<6; ++i)
      variance += ((double)val[i] - mean) * ((double)val[i] - mean);
    variance /= 6;
    double stddev = sqrt(variance);
    assert(stddev < 400.0);
  }

}

namespace study {

  void ch5_test() {
    testCountOneBits();
    testParity();
    testSwapBits();
    testClosestIntSameBitCount();
    testArithmetic();
    testReverse();
    testIsPalindrome();
    testUniformRandom();
  }

}


