
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "ch10.hpp"

using namespace std;
using namespace study;

namespace {

  void testIsBalanced() {
    cout << "[ch10] IsBalanced" << endl;
    assert(IsBalanced(unique_ptr<BSTNode<int>>()));
    assert(IsBalanced(unique_ptr<BSTNode<int>>(new BSTNode<int>())));
    assert(!IsBalanced(buildTreeFigure10_1()));
    assert(IsBalanced(buildTreeFigure10_2()));
    unique_ptr<BSTNode<int>> tree(new BSTNode<int>());
    tree->left.reset(new BSTNode<int>());
    assert(tree);
  }

  void testIsSymmetric() {
    cout << "[ch10] IsSymmetric" << endl;
    assert(IsSymmetric(buildTreeFigure10_3a()));
    assert(!IsSymmetric(buildTreeFigure10_3b()));
    assert(!IsSymmetric(buildTreeFigure10_3c()));
    assert(IsSymmetric(unique_ptr<BSTNode<int>>()));
    assert(IsSymmetric(unique_ptr<BSTNode<int>>(new BSTNode<int>())));
  }

  void testLCA() {
    cout << "[ch10] LCA" << endl;
    std::unique_ptr<BSTNode<int>> tree = buildTreeFigure10_1();
    auto ancester = LCA(tree,
                        tree->right->left->right->left->right,
                        tree->right->right->right);
    assert(ancester->data == 6);
    tree = buildTreeFigure10_1(true);
    ancester = LCA(tree->right->left->right->left->right,
                   tree->right->right->right);
    assert(ancester->data == 6);
  }

  void testSumRootToLeaf() {
    cout << "[ch10] SumRootToLeaf" << endl;
    assert(SumRootToLeaf(buildTreeFigure10_4()) == 126);
  }

  void testHasPathSum() {
    cout << "[ch10] HasPathSum" << endl;
    auto tree = buildTreeFigure10_1();
    assert(HasPathSum(tree, 591));
    assert(HasPathSum(tree, 619));
    assert(HasPathSum(tree, 1365));
    assert(!HasPathSum(tree, 314));
    assert(!HasPathSum(tree, 0));
  }

  void testFindKthNode() {
    cout << "[ch10] FindKthNode" << endl;
    auto tree = buildTreeFigure10_1();
    assert(FindKthNode(tree, 1)->data == 28);
    assert(FindKthNode(tree, 2)->data == 271);
    assert(FindKthNode(tree, 3)->data == 0);
    assert(FindKthNode(tree, 4)->data == 6);
    assert(FindKthNode(tree, 5)->data == 561);
    assert(FindKthNode(tree, 6)->data == 17);
    assert(FindKthNode(tree, 7)->data == 3);
    assert(FindKthNode(tree, 8)->data == 314);
  }

  void testFindSuccessor() {
    cout << "[ch10] FindSuccessor" << endl;
    auto tree = buildTreeFigure10_1(true);
    assert(FindSuccessor(tree)->data == 2);
    assert(FindSuccessor(tree->left->left)->data == 0);
    assert(FindSuccessor(tree->left->left->right)->data == 6);
    assert(FindSuccessor(tree->left->right->right)->data == 314);
    assert(FindSuccessor(tree->right->right->right) == nullptr);
  }

  void testInorderTraversalConstantSpace() {
    cout << "[ch10] InorderTraversalConstantSpace" << endl;
    auto tree = buildTreeFigure10_1(true);
    auto results = InorderTraversalConstantSpace(tree);
    assert(results == vector<int>({28, 271, 0, 6, 561, 17, 3, 314, 2, 401, 641, 1, 257, 6, 271, 28}));
  }

}


namespace study {

  void ch10_test() {
    testIsBalanced();
    testIsSymmetric();
    testLCA();
    testSumRootToLeaf();
    testHasPathSum();
    testFindKthNode();
    testFindSuccessor();
    testInorderTraversalConstantSpace();
  }

}


