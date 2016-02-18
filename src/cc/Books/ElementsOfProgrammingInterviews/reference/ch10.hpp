
#ifndef Books_ElementsOfProgrammingInterviews_reference_ch10_hpp
#define Books_ElementsOfProgrammingInterviews_reference_ch10_hpp

#include "Common/Tree.hpp"

#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace reference {

  extern bool IsBalanced(const std::unique_ptr<study::BSTNode<int>> &tree);

  extern bool IsSymmetric(const std::unique_ptr<study::BSTNode<int>> &tree);

  extern study::BSTNode<int> *LCA(const std::unique_ptr<study::BSTNode<int>> &tree,
                           const std::unique_ptr<study::BSTNode<int>> &node0,
                           const std::unique_ptr<study::BSTNode<int>> &node1);

  extern study::BSTNode<int> *LCA(const std::unique_ptr<study::BSTNode<int>> &node0,
                           const std::unique_ptr<study::BSTNode<int>> &node1);

  extern int SumRootToLeaf(const std::unique_ptr<study::BSTNode<int>> &tree);

  extern bool HasPathSum(const std::unique_ptr<study::BSTNode<int>> &tree, int target_sum);

  extern const study::BSTNode<int> *FindKthNode(const std::unique_ptr<study::BSTNode<int>> &tree, size_t k);

  extern const study::BSTNode<int> *FindSuccessor(const std::unique_ptr<study::BSTNode<int>> &tree);

  extern std::vector<int> InorderTraversalConstantSpace(const std::unique_ptr<study::BSTNode<int>> &tree);

}

#endif // Books_ElementsOfProgrammingInterviews_reference_ch10_hpp
