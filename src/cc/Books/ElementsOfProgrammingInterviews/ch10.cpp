
#include "ch10.hpp"
#include "reference/ch10.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

extern "C" {
#include <math.h>
}

using namespace std;

namespace study {

  bool IsBalanced(const std::unique_ptr<BSTNode<int>> &tree) {
    return reference::IsBalanced(tree);
  }

  bool IsSymmetric(const std::unique_ptr<BSTNode<int>> &tree) {
    return reference::IsSymmetric(tree);
  }

  BSTNode<int> *LCA(const std::unique_ptr<BSTNode<int>> &tree,
                    const std::unique_ptr<BSTNode<int>> &node0,
                    const std::unique_ptr<BSTNode<int>> &node1) {
    return reference::LCA(tree, node0, node1);
  }

  BSTNode<int> *LCA(const std::unique_ptr<BSTNode<int>> &node0,
                    const std::unique_ptr<BSTNode<int>> &node1) {
    return reference::LCA(node0, node1);
  }

  int SumRootToLeaf(const std::unique_ptr<BSTNode<int>> &tree) {
    return reference::SumRootToLeaf(tree);
  }

  bool HasPathSum(const std::unique_ptr<BSTNode<int>> &tree, int target_sum) {
    return reference::HasPathSum(tree, target_sum);
  }

  const BSTNode<int> *FindKthNode(const std::unique_ptr<BSTNode<int>> &tree, size_t k) {
    return reference::FindKthNode(tree, k);
  }

  const BSTNode<int> *FindSuccessor(const std::unique_ptr<BSTNode<int>> &tree) {
    return reference::FindSuccessor(tree);
  }

  std::vector<int> InorderTraversalConstantSpace(const std::unique_ptr<BSTNode<int>> &tree) {
    return reference::InorderTraversalConstantSpace(tree);
  }

}
