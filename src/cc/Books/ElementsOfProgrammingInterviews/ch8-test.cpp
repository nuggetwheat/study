
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <random>
#include <sstream>
#include <vector>

#include "ch8.hpp"

using namespace std;
using namespace study;

namespace {

  default_random_engine g_re(42);
  uniform_int_distribution<unsigned int> g_dist;

  std::shared_ptr<ListNode<int>> loadList(int k) {
    auto list = make_shared<ListNode<int>>();  
    int val {};
    std::shared_ptr<ListNode<int>> ptr = list, del_ptr;
    ptr->data = val++;
    while (val < k) {
      ptr->next = make_shared<ListNode<int>>();
      ptr = ptr->next;
      ptr->data = val++;
    }
    return list;
  }

  vector<int> listToVector(const std::shared_ptr<ListNode<int>> &list) {
    vector<int> output;
    for (auto ptr = list; ptr; ptr = ptr->next)
      output.push_back(ptr->data);
    return output;
  }

  std::shared_ptr<ListNode<int>> toList(std::initializer_list<int> values) {
    std::shared_ptr<ListNode<int>> list, ptr;
    for (auto value : values) {
      if (!list) {
        list = std::make_shared<ListNode<int>>();
        ptr = list;
        ptr->data = value;
      }
      else {
        ptr->next = std::make_shared<ListNode<int>>();
        ptr->next->data = value;
        ptr = ptr->next;
      }
    }
    return list;
  }


  void displayList(const std::shared_ptr<ListNode<int>> &list) {
    for (auto ptr = list; ptr; ptr = ptr->next)
      cout << ptr->data << " ";
    cout << endl;
  }

  void testMergeTwoSortedLists() {
    cout << "[ch8] MergeTwoSortedLists" << endl;
    std::shared_ptr<ListNode<int>> l1 = make_shared<ListNode<int>>();
    std::shared_ptr<ListNode<int>> ptr = l1;
    ptr->data = 2;
    ptr->next = make_shared<ListNode<int>>();
    ptr = ptr->next;
    ptr->data = 5;
    ptr->next = make_shared<ListNode<int>>();
    ptr = ptr->next;
    ptr->data = 7;
    std::shared_ptr<ListNode<int>> l2 = make_shared<ListNode<int>>();
    ptr = l2;
    ptr->data = 3;
    ptr->next = make_shared<ListNode<int>>();
    ptr = ptr->next;
    ptr->data = 11;
    ptr = MergeTwoSortedLists(l1, l2);
    vector<int> expected { 2, 3, 5, 7, 11 };
    vector<int> result;
    while (ptr) {
      result.push_back(ptr->data);
      ptr = ptr->next;
    }
    assert(result == expected);
  }

  void testReverseLinkedList() {
    cout << "[ch8] ReverseLinkedList" << endl;
    vector<int> input { 2, 5, 7, 3, 11 };
    std::shared_ptr<ListNode<int>> list, ptr;
    for (auto val : input) {
      if (!list) {
        list = make_shared<ListNode<int>>();
        list->data = val;
        ptr = list;
      }
      else {
        ptr->next = make_shared<ListNode<int>>();
        ptr->next->data = val;
        ptr = ptr->next;
      }
    }
    auto rlist = ReverseLinkedList(list);
    vector<int> expected { 11, 3, 7, 5, 2 };
    vector<int> output;
    for (ptr = rlist; ptr; ptr = ptr->next)
      output.push_back(ptr->data);
    assert(output == expected);
  }

  void testHasCycle() {
    cout << "[ch8] HasCycle" << endl;
    int val {};
    std::shared_ptr<ListNode<int>> list = make_shared<ListNode<int>>();
    std::shared_ptr<ListNode<int>> ptr = list, cycle_ptr;
    ptr->data = val++;
    while (val < 10) {
      ptr->next = make_shared<ListNode<int>>();
      ptr = ptr->next;
      if (val == 5)
        cycle_ptr = ptr;
      ptr->data = val++;
    }
    assert(!HasCycle(list));
    // Add a cycle
    ptr->next = cycle_ptr;
    assert(HasCycle(list) == cycle_ptr);
  }

  void testOverlappingNoCycleLists() {
    cout << "[ch8] OverlappingNoCycleLists" << endl;
    int val {};
    std::shared_ptr<ListNode<int>> list1 = make_shared<ListNode<int>>();
    std::shared_ptr<ListNode<int>> ptr = list1;
    ptr->data = val++;
    while (val < 10) {
      ptr->next = make_shared<ListNode<int>>();
      ptr = ptr->next;
      ptr->data = val++;
    }
    std::shared_ptr<ListNode<int>> list2 = make_shared<ListNode<int>>();
    ptr = list2;
    ptr->data = val++;
    ptr->next = make_shared<ListNode<int>>();
    ptr = ptr->next;
    ptr->data = val++;
    assert(!OverlappingNoCycleLists(list1, list2));
    ptr->next = list1->next;
    assert(OverlappingNoCycleLists(list1, list2));
  }

  void testDeleteFromList() {
    cout << "[ch8] DeleteFromList" << endl;
    int val {};
    std::shared_ptr<ListNode<int>> list = make_shared<ListNode<int>>();
    std::shared_ptr<ListNode<int>> ptr = list, del_ptr;
    ptr->data = val++;
    while (val < 5) {
      ptr->next = make_shared<ListNode<int>>();
      ptr = ptr->next;
      if (val == 3)
        del_ptr = ptr;
      ptr->data = val++;
    }
    DeleteFromList(del_ptr);
    vector<int> expected { 0, 1, 2, 4 };
    vector<int> output;
    for (ptr = list; ptr; ptr = ptr->next)
      output.push_back(ptr->data);
    assert(output == expected);
  }

  void testRemoveKthLast() {
    cout << "[ch8] RemoveKthLast" << endl;
    auto list = loadList(10);
    auto ret = RemoveKthLast(list, 2);
    vector<int> expected { 0, 1, 2, 3, 4, 5, 6, 7, 9 };
    assert(listToVector(list) == expected);
    list = loadList(10);
    ret = RemoveKthLast(list, 10);
    expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(listToVector(list) == expected);
  }

  void testRemoveDuplicates() {
    cout << "[ch8] RemoveDuplicates" << endl;
    auto list = toList({ 2, 2, 3, 5, 7, 7, 7, 11, 11 });
    RemoveDuplicates(list);
    vector<int> expected = { 2, 3, 5, 7, 11 };
    assert(listToVector(list) == expected);
  }

  void testCyclicallyRightShiftList() {
    cout << "[ch8] CyclicallyRightShiftList" << endl;
    auto list = toList({ 2, 3, 5, 3, 2 });
    CyclicallyRightShiftList(list, 3);
    vector<int> expected = { 5, 3, 2, 2, 3 };
    assert(listToVector(list) == expected);
    CyclicallyRightShiftList(list, 7);
    expected = { 2, 3, 5, 3, 2 };
    assert(listToVector(list) == expected);
    (void)displayList;
  }

  void testEvenOddMerge() {
    cout << "[ch8] EvenOddMerge" << endl;
    auto list = toList({ 0, 1, 2, 3, 4 });
    EvenOddMerge(list);
    vector<int> expected = { 0, 2, 4, 1, 3 };
    assert(listToVector(list) == expected);
  }

  void testIsPalindrome() {
    cout << "[ch8] IsPalindrome" << endl;
    auto list = toList({ 2, 3, 5, 3, 2 });
    assert(IsPalindrome(list));
    list = toList({ 2, 3, 5, 7, 3, 2 });
    assert(!IsPalindrome(list));
  }

  void testPivotList() {
    cout << "[ch8] PivotList" << endl;
    auto list = toList({ 3, 2, 2, 11, 7, 5, 11 });
    PivotList(list, 7);
    vector<int> expected = { 3, 2, 2, 5, 7, 11, 11 };
    assert(listToVector(list) == expected);
  }

  void testAddNumbers() {
    cout << "[ch8] AddNumbers" << endl;
    auto list1 = toList({ 3, 1, 4 });
    auto list2 = toList({ 7, 0, 9 });
    auto result = AddNumbers(list1, list2);
    vector<int> expected = { 0, 2, 3, 1 };
    assert(listToVector(result) == expected);
  }


}

namespace study {

  void ch8_test() {
    testMergeTwoSortedLists();
    testReverseLinkedList();
    testHasCycle();
    testOverlappingNoCycleLists();
    testDeleteFromList();
    testRemoveKthLast();
    testRemoveDuplicates();
    testCyclicallyRightShiftList();
    testEvenOddMerge();
    testIsPalindrome();
    testPivotList();
    testAddNumbers();
  }

}


