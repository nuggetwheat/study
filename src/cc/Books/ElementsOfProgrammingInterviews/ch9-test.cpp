
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

#include "ch9.hpp"

using namespace std;
using namespace study;

namespace {

  void testStackWithMax() {
    cout << "[ch9] StackWithMax" << endl;
    vector<int> result;
    StackWithMax mystack;
    mystack.push(2);
    result.push_back(mystack.max());
    mystack.push(2);
    result.push_back(mystack.max());
    mystack.push(1);
    result.push_back(mystack.max());
    mystack.push(4);
    result.push_back(mystack.max());
    mystack.push(5);
    result.push_back(mystack.max());
    mystack.push(5);
    result.push_back(mystack.max());
    mystack.push(3);
    result.push_back(mystack.max());
    mystack.pop();
    result.push_back(mystack.max());
    mystack.pop();
    result.push_back(mystack.max());
    mystack.pop();
    result.push_back(mystack.max());
    mystack.pop();
    result.push_back(mystack.max());
    mystack.push(0);
    result.push_back(mystack.max());
    mystack.push(3);
    result.push_back(mystack.max());
    assert(result == vector<int>({ 2, 2, 2, 4, 5, 5, 5, 5, 5, 4, 2, 2, 3 }));;
  }


  void testPolishConversion() {
    cout << "[ch9] PolishConversion" << endl;
    // Polish -> ReversePolish -> Polish
    assert(PolishToReversePolish(ReversePolishToPolish("1729")) == "1729");
    assert(PolishToReversePolish(ReversePolishToPolish("3,4,+,2,*,1,+")) == "3,4,+,2,*,1,+");
    assert(PolishToReversePolish(ReversePolishToPolish("3,4,+,2,1,*,+")) == "3,4,+,2,1,*,+");
    assert(PolishToReversePolish(ReversePolishToPolish("1,1,+,-2,*")) == "1,1,+,-2,*");
    assert(PolishToReversePolish(ReversePolishToPolish("-641,6,/,28,/")) == "-641,6,/,28,/");
    // ReversePolish -> Polish -> ReversePolish
    assert(ReversePolishToPolish(PolishToReversePolish("1729")) == "1729");
    assert(ReversePolishToPolish(PolishToReversePolish("+,*,+,3,4,2,1")) == "+,*,+,3,4,2,1");
    assert(ReversePolishToPolish(PolishToReversePolish("+,+,3,4,*,2,1")) == "+,+,3,4,*,2,1");
    assert(ReversePolishToPolish(PolishToReversePolish("*,+,1,1,-2")) == "*,+,1,1,-2");
    assert(ReversePolishToPolish(PolishToReversePolish("/,/,-641,6,28")) == "/,/,-641,6,28");
  }

  void testEvalReversePolish() {
    cout << "[ch9] EvalReversePolish" << endl;
    assert(EvalReversePolish("1729") == 1729);
    assert(EvalReversePolish("3,4,+,2,*,1,+") == 15);
    assert(EvalReversePolish("3,4,+,2,1,*,+") == 9);
    assert(EvalReversePolish("1,1,+,-2,*") == -4);
    assert(EvalReversePolish("-641,6,/,28,/") == -3);
  }

  void testEvalPolish() {
    cout << "[ch9] EvalPolish" << endl;
    assert(EvalPolish("1729") == 1729);
    assert(EvalPolish("+,*,+,3,4,2,1") == 15);
    assert(EvalPolish("+,+,3,4,*,2,1") == 9);
    assert(EvalPolish("*,+,1,1,-2") == -4);
    assert(EvalPolish("/,/,-641,6,28") == -3);
  }

  void testIsWellFormed() {
    cout << "[ch9] IsWellFormed" << endl;
    assert(IsWellFormed("{()}"));
    assert(IsWellFormed("({()}()[])"));
    assert(!IsWellFormed("(}"));
    assert(!IsWellFormed("({)}"));
  }

  void testShortestEquivalentPath() {
    cout << "[ch9] ShortestEquivalentPath" << endl;
    assert(ShortestEquivalentPath("/foo/bar/../baz/") == "/foo/baz/");
    assert(ShortestEquivalentPath("/foo/./bar/../wow.txt")  == "/foo/wow.txt");
  }

  void testBSTInSortedOrder() {
    cout << "[ch9] BSTInSortedOrder" << endl;
    std::unique_ptr<BSTNode<int>> tree(new BSTNode<int>());
    BSTNode<int> *node = tree.get();
    node->data = 43;
    node->right.reset(new BSTNode<int>());
    node = node->right.get();
    node->data = 47;
    node->right.reset(new BSTNode<int>());
    node = node->right.get();
    node->data = 53;
    node = tree.get();
    node->left.reset(new BSTNode<int>());
    node = node->left.get();
    node->data = 23;
    node->right.reset(new BSTNode<int>());
    node = node->right.get();
    node->data = 37;
    node->right.reset(new BSTNode<int>());
    node->right->data = 41;
    node->left.reset(new BSTNode<int>());
    node = node->left.get();
    node->data = 29;
    node->right.reset(new BSTNode<int>());
    node->right->data = 31;
    auto result = BSTInSortedOrder(tree);
    vector<int> expected { 23, 29, 31, 37, 41, 43, 47, 53 };
    assert(result == expected);
  }

  std::shared_ptr<PostingListNode> createPostingList() {
    std::vector<std::shared_ptr<PostingListNode>> nv;
    std::shared_ptr<PostingListNode> list = std::make_shared<PostingListNode>();
    auto node = list;
    nv.push_back(node);
    node->next = std::make_shared<PostingListNode>();
    node = node->next;
    nv.push_back(node);
    node->next = std::make_shared<PostingListNode>();
    node = node->next;
    nv.push_back(node);
    node->next = std::make_shared<PostingListNode>();
    node = node->next;
    nv.push_back(node);
    nv[0]->jump = nv[2];
    nv[1]->jump = nv[3];
    nv[2]->jump = nv[1];
    nv[3]->jump = nv[3];
    return list;
  }

  std::vector<int> postingListToVector(const std::shared_ptr<PostingListNode> &list) {
    std::vector<int> result;
    auto node = list;
    while (node) {
      result.push_back(node->order);
      node = node->next;
    }
    return result;
  }

  struct PostingListNode {
    int order {-1};
    struct PostingListNode *jump {};
    std::shared_ptr<PostingListNode> next;
  };

  void testSetJumpOrder() {
    cout << "[ch9] SetJumpOrder" << endl;
    vector<int> expected { 0, 2, 1, 3 };
    auto list = createPostingList();
    SetJumpOrderRecursive(list);
    auto result = postingListToVector(list);
    assert(result == expected);
    list = createPostingList();
    SetJumpOrderIterative(list);
    result = postingListToVector(list);
    assert(result == expected);
  }

  void testExamineBuildingsWithSunset() {
    cout << "[ch9] ExamineBuildingsWithSunset" << endl;
    istringstream iss("333 750 100 320 125");
    vector<size_t> result, expected { 4, 3, 1 };
    result = ExamineBuildingsWithSunset(&iss);
    assert(result == expected);
    iss = istringstream("8 7 6 5 4 3 2 15");
    result = ExamineBuildingsWithSunset(&iss);
    assert(result == vector<size_t>({7}));
  }

  void testSortDescending() {
    cout << "[ch9] SortDescending" << endl;
    stack<int> mystack;
    mystack.push(5);
    mystack.push(4);
    mystack.push(3);
    mystack.push(2);
    mystack.push(1);
    SortDescending(&mystack);
    for (int last = std::numeric_limits<int>::max(); !mystack.empty(); mystack.pop())
      assert(mystack.top() <= last);
    mystack.push(2);
    mystack.push(5);
    mystack.push(3);
    mystack.push(4);
    mystack.push(1);
    SortDescending(&mystack);
    for (int last = std::numeric_limits<int>::max(); !mystack.empty(); mystack.pop())
      assert(mystack.top() <= last);
  }

  void testBinaryTreeDepthOrder() {
    cout << "[ch9] BinaryTreeDepthOrder" << endl;
    vector<vector<int>> expected;
    expected.push_back( {314} );
    expected.push_back( {6,6} );
    expected.push_back( {271,561,2,271} );
    expected.push_back( {28,0,3,1,28} );
    expected.push_back( {17,401,257} );
    expected.push_back( {641} );
    auto result = BinaryTreeDepthOrder( buildTreeFigure10_1() );
    assert(result == expected);
  }

  void testQueueImplementedWithStacks() {
    cout << "[ch9] QueueImplementedWithStacks" << endl;
    QueueImplementedWithStacks qiws;
    queue<int> q;
    q.push(42);
    qiws.enqueue(42);
    q.push(5);
    qiws.enqueue(5);
    assert(q.front() == qiws.dequeue());
    q.pop();
    q.push(4);
    qiws.enqueue(4);
    q.push(8);
    qiws.enqueue(8);
    q.push(10);
    qiws.enqueue(10);
    assert(q.front() == qiws.dequeue());
    q.pop();
    assert(q.front() == qiws.dequeue());
    q.pop();
    q.push(9);
    qiws.enqueue(9);
    q.push(3);
    qiws.enqueue(3);
    while (!q.empty()) {
      assert(q.front() == qiws.dequeue());
      q.pop();
    }
  }

  void testQueueWithMax() {
    cout << "[ch9] QueueWithMax" << endl;
    QueueWithMax myQueue;
    vector<int> result;
    myQueue.enqueue(3);
    result.push_back(myQueue.max());
    myQueue.enqueue(1);
    result.push_back(myQueue.max());
    myQueue.enqueue(3);
    result.push_back(myQueue.max());
    myQueue.enqueue(2);
    result.push_back(myQueue.max());
    myQueue.enqueue(0);
    result.push_back(myQueue.max());
    myQueue.enqueue(1);
    result.push_back(myQueue.max());
    myQueue.dequeue();
    result.push_back(myQueue.max());
    myQueue.dequeue();
    result.push_back(myQueue.max());
    myQueue.enqueue(2);
    result.push_back(myQueue.max());
    myQueue.enqueue(4);
    result.push_back(myQueue.max());
    myQueue.dequeue();
    result.push_back(myQueue.max());
    myQueue.enqueue(4);
    result.push_back(myQueue.max());
    assert(result == vector<int>({3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4}));
  }

}


namespace study {

  void ch9_test() {
    testStackWithMax();
    testPolishConversion();
    testEvalReversePolish();
    testEvalPolish();
    testIsWellFormed();
    testShortestEquivalentPath();
    testBSTInSortedOrder();
    testSetJumpOrder();
    testExamineBuildingsWithSunset();
    testSortDescending();
    testBinaryTreeDepthOrder();
    testQueueImplementedWithStacks();
    testQueueWithMax();
  }

}


