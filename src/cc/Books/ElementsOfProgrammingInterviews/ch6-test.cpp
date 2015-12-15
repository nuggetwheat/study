
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <random>
#include <sstream>
#include <vector>

#include "ch6.hpp"

using namespace std;
using namespace study;

namespace {

  default_random_engine g_re(42);
  uniform_int_distribution<unsigned int> g_dist;

  void testDutchFlagPartition() {
    cout << "[ch6] DutchFlagPartition" << endl;
    vector<int> data(1000);
    {
      uniform_int_distribution<int> dist(0, 2);
      auto rng = bind(dist, g_re);
      generate_n(data.begin(), 100, rng);
      for (size_t i=0; i<100; ++i)
        DutchFlagPartition(i, &data);
    }
    {
      uniform_int_distribution<int> dist(0, 100);
      auto rng = bind(dist, g_re);
      generate_n(data.begin(), 100, rng);
      for (size_t i=0; i<100; ++i)
        DutchFlagPartition(i, &data);
    }
  }

  int64_t digitVectorToInt(vector<int> A) {
    assert(!A.empty());
    bool isNegative = A.front() < 0;
    if (isNegative)
      A.front() *= -1;
    int64_t rval {};
    auto iter = A.begin();
    while (iter != A.end() && *iter == 0)
      ++iter;
    while (iter != A.end()) {
      rval = *iter + (rval * 10);
      ++iter;
    }
    return isNegative ? -rval : rval;
  }

  void testPlusOne() {
    cout << "[ch6] PlusOne" << endl;
    uniform_int_distribution<int> dist(0, 9);
    auto rng = bind(dist, g_re);
    vector<int> input(19);
    for (size_t i=0; i<100; ++i) {
      generate(input.begin(), input.end(),
               [&rng]() -> int { return rng(); });
      auto output = PlusOne(input);
      assert(digitVectorToInt(output) == digitVectorToInt(input)+1);
    }
  }

  void testMultiply() {
    cout << "[ch6] Multiply" << endl;
    uniform_int_distribution<int> dist(0, 9);
    auto rng = bind(dist, g_re);
    vector<int> num1(8);
    vector<int> num2(8);
    for (size_t i=0; i<1000; ++i) {
      generate(num1.begin(), num1.end(),
               [&rng]() -> int { return rng(); });
      generate(num2.begin(), num2.end(),
               [&rng]() -> int { return rng(); });
      if (rng() & 1)
        num1.front() *= -1;
      if (rng() & 1)
        num2.front() *= -1;
      auto output = Multiply(num1, num2);
      assert(digitVectorToInt(output) == digitVectorToInt(num1)*digitVectorToInt(num2));
    }
  }

  void testCanReachEnd() {
    cout << "[ch6] CanReachEnd" << endl;
    vector<int> max_advance_steps;
    max_advance_steps = { 3, 3, 1, 0, 2, 0, 1 };
    assert(CanReachEnd(max_advance_steps));
    max_advance_steps = { 3, 2, 0, 0, 2, 0, 1 };
    assert(!CanReachEnd(max_advance_steps));
    max_advance_steps = { 2, 4, 1, 1, 0, 2, 3 };
    assert(CanReachEnd(max_advance_steps));
  }

  void testFewestStepsToEnd() {
    cout << "[ch6] FewestStepsToEnd" << endl;
    vector<int> max_advance_steps;
    max_advance_steps = { 3, 3, 1, 0, 2, 0, 1 };
    assert(FewestStepsToEnd(max_advance_steps) == 3);
    max_advance_steps = { 3, 2, 0, 0, 2, 0, 1 };
    assert(FewestStepsToEnd(max_advance_steps) == numeric_limits<int>::max());
    max_advance_steps = { 2, 4, 1, 1, 0, 2, 3 };
    assert(FewestStepsToEnd(max_advance_steps) == 3);
  }

  void testDeleteKey() {
    cout << "[ch6] DeleteKey" << endl;
    vector<int> data;
    data = { 5, 3, 7, 11, 2, 3, 13, 5, 7 };
    size_t end = DeleteKey(3, &data);
    assert(end == 7);
    data.resize(end);
    initializer_list<int> expected { 5, 7, 11, 2, 13, 5, 7 };
    assert(equal(data.begin(), data.end(), expected.begin()));
    uniform_int_distribution<int> dist(0, 9);
    auto rng = bind(dist, g_re);
    data.resize(1000);
    generate_n(data.begin(), 1000, rng);
    end = DeleteKey(7, &data);
    vector<int> data2(1000);
    generate_n(data2.begin(), 1000, rng);
    auto endIter = remove(data2.begin(), data2.end(), 7);
    assert(end == (size_t)(endIter - data2.begin()));
    assert(equal(data2.begin(), endIter, data.begin()));
  }

  void testDeleteDuplicates() {
    cout << "[ch6] DeleteDuplicates" << endl;
    vector<int> data;
    uniform_int_distribution<int> dist(0, 100);
    auto rng = bind(dist, g_re);
    data.resize(10000);
    generate_n(data.begin(), 10000, rng);
    sort(data.begin(), data.end());
    vector<int> data2 = data;
    auto newSize = DeleteDuplicates(&data);
    auto newEnd = unique(data2.begin(), data2.end());
    data.resize(newSize);
    data2.erase(newEnd, data2.end());
    assert(data == data2);
  }

  void testBuyAndSellStockOnce() {
    cout << "[ch6] BuyAndSellStockOnce" << endl;
    vector<int> data;
    data = { 310, 315, 275, 295, 260, 270, 290, 230, 255, 250 };
    assert(BuyAndSellStockOnce(data) == 30);
  }

  void testBuyAndSellStockTwice() {
    cout << "[ch6] BuyAndSellStockTwice" << endl;
    vector<int> data;
    data = { 12, 11, 13, 9, 12, 8, 14, 13, 15 };
    assert(BuyAndSellStockTwice(data) == 10);
  }

  void testGeneratePrimes() {
    cout << "[ch6] GeneratePrimes" << endl;
    auto primes = GeneratePrimes(18);
    initializer_list<int> expected { 2, 3, 5, 7, 11, 13, 17 };
    assert(equal(primes.begin(), primes.end(), expected.begin()));
  }

  void testApplyPermutation() {
    cout << "[ch6] ApplyPermutation" << endl;
    vector<int> A { 1, 2, 3, 4 };
    vector<int> perm { 2, 0, 1, 3 };
    ApplyPermutation(perm, &A);
    assert(equal(A.begin(), A.end(), initializer_list<int>({ 2, 3, 1, 4 }).begin()));
  }

  void testPermutation() {
    cout << "[ch6] Permutation" << endl;
    vector<int> data, result;

    // next
    data = { 0, 1, 2, 3, 4, 5 };
    result = { 0, 1, 2, 3, 4, 5 };
    while (next_permutation(data.begin(), data.end())) {
      result = NextPermutation(result);
      assert(equal(data.begin(), data.end(), result.begin()));
    }
    
    // prev
    data = { 0, 1, 2, 3, 4, 5 };
    result = { 0, 1, 2, 3, 4, 5 };
    while (next_permutation(data.begin(), data.end())) {
      result = NextPermutation(result);
      assert(equal(data.begin(), data.end(), result.begin()));
    }
                     
  }

  void testComputeRandomPermutation() {
    cout << "[ch6] ComputeRandomPermutation" << endl;
    vector<int> result = ComputeRandomPermutation(20);
    assert(equal(result.begin(), result.end(),
                 initializer_list<int>({18, 15, 1, 3, 6, 13, 8, 12, 7, 5, 9, 2, 11, 4, 10, 14, 0, 16, 17, 19 }).begin()));
  }

  void testComputeRandomSubset() {
    cout << "[ch6] ComputeRandomSubset" << endl;
    auto result = ComputeRandomSubset(50, 7);
    assert(equal(result.begin(), result.end(),
                 initializer_list<int>({26, 36, 13, 18, 9, 48, 25}).begin()));
  }

  void testRotateMatrix() {
    cout << "[ch6] RotateMatrix" << endl;
    std::vector<std::vector<int>> A(4);
    for (int i=0; i<16; ++i)
      A[i/4].push_back(i + 1);
    RotateMatrix(&A);
    std::vector<int> result;
    result.reserve(16);
    for (int i=0; i<4; ++i)
      for (int j=0; j<4; ++j)
        result.push_back(A[i][j]);
    assert(equal(result.begin(), result.end(),
                 initializer_list<int>({13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3, 16, 12, 8, 4 }).begin()));
  }

}

namespace study {

  void ch6_test() {
    testDutchFlagPartition();
    testPlusOne();
    testMultiply();
    testCanReachEnd();
    testFewestStepsToEnd();
    testDeleteKey();
    testDeleteDuplicates();
    testBuyAndSellStockOnce();
    testBuyAndSellStockTwice();
    testGeneratePrimes();
    testApplyPermutation();
    testPermutation();
    testComputeRandomPermutation();
    testComputeRandomSubset();
    testRotateMatrix();
  }

}


