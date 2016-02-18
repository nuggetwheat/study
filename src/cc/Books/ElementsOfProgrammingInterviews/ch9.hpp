
#ifndef Books_ElementsOfProgrammingInterviews_ch9_hpp
#define Books_ElementsOfProgrammingInterviews_ch9_hpp

#include "reference/ch9.hpp"

#include "Common/Tree.hpp"

#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace study {

  class StackWithMax : public reference::StackWithMax {
  public:
    void push(int x) override;
    int pop() override;
    int max() const override;
  };

  extern std::string PolishToReversePolish(const std::string &expression);

  extern std::string ReversePolishToPolish(const std::string &expression);

  extern int EvalReversePolish(const std::string &expression);

  extern int EvalPolish(const std::string &expression);

  extern bool IsWellFormed(const std::string &expr);

  extern std::string ShortestEquivalentPath(const std::string &path);

  extern std::vector<int> BSTInSortedOrder(const std::unique_ptr<BSTNode<int>> &tree);

  extern void SetJumpOrderRecursive(const std::shared_ptr<reference::PostingListNode> &list);

  extern void SetJumpOrderIterative(const std::shared_ptr<reference::PostingListNode> &list);

  extern std::vector<size_t> ExamineBuildingsWithSunset(std::istringstream *sin);

  extern void SortDescending(std::stack<int> *sp);

  extern std::vector<std::vector<int>> BinaryTreeDepthOrder(const std::unique_ptr<BSTNode<int>> &tree);

  class QueueImplementedWithStacks : public reference::QueueImplementedWithStacks {
  public:
    void enqueue(int x) override;
    int dequeue() override;
  };

  class QueueWithMax : public reference::QueueWithMax {
  public:
    void enqueue(int x) override;
    int dequeue() override;
    int max() const override;
  };

}

#endif // Books_ElementsOfProgrammingInterviews_ch9_hpp
