
#ifndef Books_ElementsOfProgrammingInterviews_reference_ch9_hpp
#define Books_ElementsOfProgrammingInterviews_reference_ch9_hpp

#include "Common/Tree.hpp"

#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace reference {

  class StackWithMax {
  public:
    StackWithMax();
    ~StackWithMax();
    virtual void push(int x);
    virtual int pop();
    virtual int max() const;
  protected:
    void *state_ {};
  };

  extern std::string PolishToReversePolish(const std::string &expression);

  extern std::string ReversePolishToPolish(const std::string &expression);

  extern int EvalReversePolish(const std::string &expression);

  extern int EvalPolish(const std::string &expression);

  extern bool IsWellFormed(const std::string &expr);

  extern std::string ShortestEquivalentPath(const std::string &path);

  extern std::vector<int> BSTInSortedOrder(const std::unique_ptr<study::BSTNode<int>> &tree);

  struct PostingListNode {
    int order {-1};
    std::shared_ptr<PostingListNode> jump, next;
  };

  extern void SetJumpOrderRecursive(const std::shared_ptr<PostingListNode> &list);

  extern void SetJumpOrderIterative(const std::shared_ptr<PostingListNode> &list);

  extern std::vector<size_t> ExamineBuildingsWithSunset(std::istringstream *sin);

  extern void SortDescending(std::stack<int> *sp);

  extern std::vector<std::vector<int>> BinaryTreeDepthOrder(const std::unique_ptr<study::BSTNode<int>> &tree);

  class QueueImplementedWithStacks {
  public:
    virtual void enqueue(int x);
    virtual int dequeue();
  protected:
    std::stack<int> estack_, dstack_;
  };

  class QueueWithMax {
  public:
    QueueWithMax();
    ~QueueWithMax();
    virtual void enqueue(int x);
    virtual int dequeue();
    virtual int max() const;
  protected:
    void *state_ {};
  };


}

#endif // Books_ElementsOfProgrammingInterviews_reference_ch9_hpp
