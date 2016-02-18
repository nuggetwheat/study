
#include "ch10.hpp"

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

namespace reference {

  pair<bool, int> checkBalanced(const std::unique_ptr<study::BSTNode<int>> &tree) {
    if (!tree)
      return {true, -1};
    auto left = checkBalanced(tree->left);
    auto right = checkBalanced(tree->right);
    int maxHeight = max(left.second, right.second);
    bool balanced = left.first && right.first && (abs(left.second - right.second) <= 1);
    return {balanced, maxHeight+1};
  }

  bool IsBalanced(const std::unique_ptr<study::BSTNode<int>> &tree) {
    return checkBalanced(tree).first;
  }

  bool isSymmetric(const std::unique_ptr<study::BSTNode<int>> &left,
                   const std::unique_ptr<study::BSTNode<int>> &right) {
    return (!left && !right) ||
      (left && right &&
       left->data == right->data &&
       isSymmetric(left->left, right->right) &&
       isSymmetric(left->right, right->left));
  }

  bool IsSymmetric(const std::unique_ptr<study::BSTNode<int>> &tree) {
    return !tree || isSymmetric(tree->left, tree->right);
  }

  pair<int, study::BSTNode<int> *> lcaHelper(const std::unique_ptr<study::BSTNode<int>> &node,
                                      const std::unique_ptr<study::BSTNode<int>> &node0,
                                      const std::unique_ptr<study::BSTNode<int>> &node1) {
    if (!node)
      return {0, nullptr};
    auto left  = lcaHelper(node->left, node0, node1);
    if (left.first == 3)
      return left;
    auto right = lcaHelper(node->right, node0, node1);
    if (right.first == 3)
      return right;
    int val = (node.get() == node0.get() ? 1 : 0) |
      (node.get() == node1.get() ? 2 : 0) |
      left.first | right.first;
    if (val == 3)
      return {3, node.get()};
    return left.first ? left : (right.first ? right : make_pair(val, nullptr));
  }


  study::BSTNode<int> *LCA(const std::unique_ptr<study::BSTNode<int>> &tree,
                    const std::unique_ptr<study::BSTNode<int>> &node0,
                    const std::unique_ptr<study::BSTNode<int>> &node1) {
    return lcaHelper(tree, node0, node1).second;
  }

  int height(study::BSTNode<int> *node) {
    int h {-1};
    while (node) {
      ++h;
      node = node->parent;
    }
    return h;
  }

  study::BSTNode<int> *LCA(const std::unique_ptr<study::BSTNode<int>> &node0,
                    const std::unique_ptr<study::BSTNode<int>> &node1) {
    int h0 = height(node0.get());
    int h1 = height(node1.get());
    study::BSTNode<int> *n0, *n1;
    
    n1 = node1.get();
    n0 = node0.get();
    if (h0 < h1) {
      while (h0 < h1) {
        n1 = n1->parent;
        --h1;
      }
    }
    else if (h1 < h0) {
      while (h1 < h0) {
        n0 = n0->parent;
        --h0;
      }
    }
    while (n0 && n0 != n1) {
      n0 = n0->parent;
      n1 = n1->parent;
    }
    return n0;
  }

  void sumRootToLeaf(const std::unique_ptr<study::BSTNode<int>> &node,
                     int *val, int *sum) {
    if (!node)
      return;
    *val = ((*val) << 1) | node->data;
    if (!node->left && !node->right)
      *sum += *val;
    else {
      if (node->left)
        sumRootToLeaf(node->left, val, sum);
      if (node->right)
        sumRootToLeaf(node->right, val, sum);
    }
    *val >>= 1;
  }

  int SumRootToLeaf(const std::unique_ptr<study::BSTNode<int>> &tree) {
    int val {};
    int sum {};
    sumRootToLeaf(tree, &val, &sum);
    return sum;
  }

  bool hasPathSum(const std::unique_ptr<study::BSTNode<int>> &node,
                  int target_sum, int running_total) {
    if (!node)
      return false;

    if (!node->left && !node->right)  // leaf
      return running_total + node->data == target_sum;

    return hasPathSum(node->left, target_sum, running_total + node->data) ||
      hasPathSum(node->right, target_sum, running_total + node->data);
  }

  bool HasPathSum(const std::unique_ptr<study::BSTNode<int>> &tree, int target_sum) {
    return hasPathSum(tree, target_sum, 0);
  }

  study::BSTNode<int> *findKthNode(const std::unique_ptr<study::BSTNode<int>> &node,
                            size_t k, size_t *seen) {
    if (!node)
      return nullptr;
    study::BSTNode<int> *kthNode = findKthNode(node->left, k, seen);
    if (kthNode == nullptr) {
      if (++(*seen) == k)
        return node.get();
      kthNode = findKthNode(node->right, k, seen);      
    }
    return kthNode;
  }


  const study::BSTNode<int> *FindKthNode(const std::unique_ptr<study::BSTNode<int>> &tree, size_t k) {
    size_t seen {};
    return findKthNode(tree, k, &seen);
  }

  const study::BSTNode<int> *FindSuccessor(const std::unique_ptr<study::BSTNode<int>> &tree) {
    const study::BSTNode<int> *ret {};
    if (tree->right)
      ret = FindKthNode(tree->right, 1);
    else if (tree->parent) {
      if (tree->parent->left.get() == tree.get())
        ret = tree->parent;
      else {
        study::BSTNode<int> *node = tree.get();
        while (node->parent && node->parent->right.get() == node)
          node = node->parent;
        if (node->parent)
          ret = node->parent;
      }
    }
    return ret;
  }

  typedef enum { PARENT, LCHILD, RCHILD } ArrivalDirection;

  std::vector<int> InorderTraversalConstantSpace(const std::unique_ptr<study::BSTNode<int>> &tree) {
    std::vector<int> results;
    study::BSTNode<int> *node = tree.get();
    int arrival_dir = PARENT;
    while (node) {
      if (arrival_dir == PARENT) {
        if (node->left)
          node = node->left.get();
        else {
          results.push_back(node->data);
          if (node->right)
            node = node->right.get();
          else {
            arrival_dir = (node->parent && node->parent->left.get() == node) ? LCHILD : RCHILD;
            node = node->parent;
          }
        }
      }
      else if (arrival_dir == LCHILD) {
        results.push_back(node->data);
        if (node->right) {
          node = node->right.get();
          arrival_dir = PARENT;
        }
        else {
          arrival_dir = (node->parent && node->parent->left.get() == node) ? LCHILD : RCHILD;
          node = node->parent;
        }
      }
      else {
        assert(arrival_dir == RCHILD);
        arrival_dir = (node->parent && node->parent->left.get() == node) ? LCHILD : RCHILD;
        node = node->parent;
      }
    }
    return results;
  }

}
