
#include "ch6.hpp"
#include "reference/ch6.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <utility>

extern "C" {
#include <math.h>
}

namespace {
  std::default_random_engine dre;
}

namespace study {
  
  void DutchFlagPartition(size_t pivot_index, std::vector<int> *A_ptr) {
    reference::DutchFlagPartition(pivot_index, A_ptr);
  }

  std::vector<int> PlusOne(std::vector<int> A) {
    return reference::PlusOne(A);
  }

  std::vector<int> Multiply(std::vector<int> num1, std::vector<int> num2) {
    return reference::Multiply(num1, num2);
  }

  bool CanReachEnd(const std::vector<int> &max_advance_steps) {
    return reference::CanReachEnd(max_advance_steps);
  }

  size_t FewestStepsToEnd(const std::vector<int> &max_advance_steps) {
    return reference::FewestStepsToEnd(max_advance_steps);
  }

  size_t DeleteKey(int key, std::vector<int> *A_ptr) {
    return reference::DeleteKey(key, A_ptr);
  }

  int DeleteDuplicates(std::vector<int> *A_ptr) {
    return reference::DeleteDuplicates(A_ptr);
  }

  int BuyAndSellStockOnce(const std::vector<int> &prices) {
    return reference::BuyAndSellStockOnce(prices);
  }

  int BuyAndSellStockTwice(const std::vector<int> &prices) {
    return reference::BuyAndSellStockTwice(prices);
  }

  std::vector<int> GeneratePrimes(int n) {
    return reference::GeneratePrimes(n);
  }

  void ApplyPermutation(std::vector<int> perm, std::vector<int> *A_ptr) {
    reference::ApplyPermutation(perm, A_ptr);
  }

  std::vector<int> NextPermutation(std::vector<int> perm) {
    return reference::NextPermutation(perm);
  }

  std::vector<int> PrevPermutation(std::vector<int> perm) {
    return reference::PrevPermutation(perm);
  }

  std::vector<int> ComputeRandomPermutation(int n) {
    return reference::ComputeRandomPermutation(n);
  }

  std::vector<int> ComputeRandomSubset(int n, int k) {
    return reference::ComputeRandomSubset(n, k);
  }

  void RotateMatrix(std::vector<std::vector<int>> *square_matrix_ptr) {
    reference::RotateMatrix(square_matrix_ptr);
  }

}
