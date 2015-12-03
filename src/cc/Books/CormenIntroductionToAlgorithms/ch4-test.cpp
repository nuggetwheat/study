
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>

#include "ch4.hpp"

using namespace std;
using namespace study;

namespace {

  default_random_engine g_re(42);
  uniform_int_distribution<unsigned int> g_dist;

  const std::initializer_list<int> OptimalTrade_data {
    100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97
  };
  const vector<int> OptimalTrade_expected { 63, 81, 101, 94 };

  void testOptimalTrade() {
    cout << "[ch4] OptimalTrade" << endl;
    {
      vector<int> trade_data { OptimalTrade_data };
      auto result = OptimalTradeMaximumSubArray(trade_data);
      assert(equal(result.begin, result.end, trade_data.begin()+7));
      assert(result.sum == 43);
    }
    {
      vector<int> trade_data { OptimalTrade_data };
      auto result = OptimalTradeBruteForce(trade_data);
      assert(equal(result.begin, result.end, trade_data.begin()+7));
      assert(result.sum == 43);
    }

    uniform_int_distribution<int> dist(0, 200);
    chrono::system_clock::time_point before;
    Trade result;

    vector<int> trade_data;
    trade_data.reserve(100);

    for (size_t i=1; i<100; ++i) {
      default_random_engine re(i);
      trade_data.resize(i);
      generate_n(trade_data.begin(), i, bind(dist, re));
      before = chrono::system_clock::now();
      result = OptimalTradeMaximumSubArray(trade_data);
      auto msa_timing = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - before).count();
      before = chrono::system_clock::now();
      result = OptimalTradeBruteForce(trade_data);
      auto bf_timing = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - before).count();
      if (bf_timing > msa_timing) {
        cout << "BruteForce vs. MaximumSubArray crossover point:  " << i << endl;
        break;
      }
    }

  }

}

namespace study {

  void ch4_test() {
    testOptimalTrade();
  }

}


