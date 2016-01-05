
#ifndef Books_ElementsOfProgrammingInterviews_ch10_hpp
#define Books_ElementsOfProgrammingInterviews_ch10_hpp

#include "Common/Tree.hpp"

#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace study {

  extern bool IsBalanced(const std::unique_ptr<BSTNode<int>> &tree);

  extern bool IsSymmetric(const std::unique_ptr<BSTNode<int>> &tree);

  extern BSTNode<int> *LCA(const std::unique_ptr<BSTNode<int>> &tree,
                           const std::unique_ptr<BSTNode<int>> &node0,
                           const std::unique_ptr<BSTNode<int>> &node1);

  extern BSTNode<int> *LCA(const std::unique_ptr<BSTNode<int>> &node0,
                           const std::unique_ptr<BSTNode<int>> &node1);

  extern int SumRootToLeaf(const std::unique_ptr<BSTNode<int>> &tree);

  extern bool HasPathSum(const std::unique_ptr<BSTNode<int>> &tree, int target_sum);

  extern const BSTNode<int> *FindKthNode(const std::unique_ptr<BSTNode<int>> &tree, size_t k);

  extern const BSTNode<int> *FindSuccessor(const std::unique_ptr<BSTNode<int>> &tree);

  extern std::vector<int> InorderTraversalConstantSpace(const std::unique_ptr<BSTNode<int>> &tree);

}

#endif // Books_ElementsOfProgrammingInterviews_ch10_hpp
