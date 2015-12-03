
#include <iostream>
#include <stdexcept>

#include "ch4.hpp"

using namespace std;
using namespace study;

namespace {

  Trade findMaxCrossingSubarray(vector<int>::iterator low,
                                vector<int>::iterator mid,
                                vector<int>::iterator high) {
    Trade result;
    int sum {};
    int left_sum {};
    result.begin = result.end = mid;
    if (mid > low) {
      for (auto iter = mid-1; iter >= low; --iter) {
        sum += *iter;
        if (sum > left_sum) {
          left_sum = sum;
          result.begin = iter;
        }
      }
    }
    sum = 0;
    int right_sum {};
    if (mid < high) {
      for (auto iter = mid; iter < high; ++iter) {
        sum += *iter;
        if (sum > right_sum) {
          right_sum = sum;
          result.end = iter+1;
        }
      }
    }
    result.sum = left_sum + right_sum;
    return result;
  }

  Trade optimalTradeMaximumSubArray(vector<int>::iterator low,
                                    vector<int>::iterator high) {
    Trade result;
    if (low == high)
      result.begin = result.end = low;
    else if (low == high-1) {
      result.begin = result.end = low;
      if (*low > 0) {
        result.end = high;
        result.sum = *low;
      }
    }
    else {
      Trade left, right, cross;
      auto mid = low + ((high-low) / 2);
      left = optimalTradeMaximumSubArray(low, mid);
      right = optimalTradeMaximumSubArray(mid, high);
      cross = findMaxCrossingSubarray(low, mid, high);
      if (left.sum >= right.sum && left.sum >= cross.sum)
        result = left;
      else if (right.sum >= left.sum && right.sum >= cross.sum)
        result = right;
      else
        result = cross;
    }
    return result;
  }


}

namespace study {


  Trade OptimalTradeMaximumSubArray(vector<int> &data) {
    vector<int> delta;
    delta.reserve(data.size());
    for (size_t i=0; i<data.size()-1; ++i)
      delta.push_back(data[i+1] - data[i]);
    Trade deltaResult = optimalTradeMaximumSubArray(delta.begin(), delta.end());
    Trade result;
    if (deltaResult.begin == deltaResult.end) {
      result.begin = result.end = data.begin();
      result.sum = 0;
    }
    else {
      result.begin = data.begin() + (deltaResult.begin - delta.begin());
      result.end = data.begin() + (deltaResult.end - delta.begin());
      result.sum = deltaResult.sum;
    }
    return result;
  }

  Trade OptimalTradeBruteForce(vector<int> &data) {
    vector<int> delta;
    delta.reserve(data.size());
    for (size_t i=0; i<data.size()-1; ++i)
      delta.push_back(data[i+1] - data[i]);
    int best_sum {};
    size_t best_low {};
    size_t best_high {};
    int sum {};
    for (size_t i=0; i<delta.size(); ++i) {
      sum = 0;
      for (size_t j=i; j<delta.size(); ++j) {
        sum += delta[j];
        if (sum > best_sum) {
          best_sum = sum;
          best_low = i;
          best_high = j+1;
        }
      }
    }
    Trade result;
    result.begin = data.begin() + best_low;
    result.end = data.begin() + best_high;
    result.sum = best_sum;
    return result;
  }



}


