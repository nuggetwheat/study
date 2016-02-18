
#include "ch8.hpp"
#include "reference/ch8.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

extern "C" {
#include <math.h>
}

using namespace std;

namespace study {

  std::shared_ptr<reference::ListNode<int>>
  MergeTwoSortedLists(std::shared_ptr<reference::ListNode<int>> l1,
                      std::shared_ptr<reference::ListNode<int>> l2) {
    return reference::MergeTwoSortedLists(l1, l2);
  }

  std::shared_ptr<reference::ListNode<int>>
  ReverseLinkedList(const std::shared_ptr<reference::ListNode<int>> &list) {
    return reference::ReverseLinkedList(list);
  }

  std::shared_ptr<reference::ListNode<int>>
  HasCycle(const std::shared_ptr<reference::ListNode<int>> &list) {
    return reference::HasCycle(list);
  }

  std::shared_ptr<reference::ListNode<int>>
  OverlappingNoCycleLists(const std::shared_ptr<reference::ListNode<int>> &l1,
                          const std::shared_ptr<reference::ListNode<int>> &l2) {
    return reference::OverlappingNoCycleLists(l1, l2);
  }

  void DeleteFromList(const std::shared_ptr<reference::ListNode<int>> &list) {
    reference::DeleteFromList(list);
  }

  std::shared_ptr<reference::ListNode<int>>
  RemoveKthLast(std::shared_ptr<reference::ListNode<int>> &list, int k) {
    return reference::RemoveKthLast(list, k);
  }

  void RemoveDuplicates(const std::shared_ptr<reference::ListNode<int>> &list) {
    reference::RemoveDuplicates(list);
  }

  void CyclicallyRightShiftList(std::shared_ptr<reference::ListNode<int>> &list, int k) {
    reference::CyclicallyRightShiftList(list, k);
  }

  void EvenOddMerge(std::shared_ptr<reference::ListNode<int>> &list) {
    reference::EvenOddMerge(list);
  }

  bool IsPalindrome(std::shared_ptr<reference::ListNode<int>> &list) {
    return reference::IsPalindrome(list);
  }

  void PivotList(std::shared_ptr<reference::ListNode<int>> &list, int k) {
    reference::PivotList(list, k);
  }

  std::shared_ptr<reference::ListNode<int>>
  AddNumbers(const std::shared_ptr<reference::ListNode<int>> &l1,
             const std::shared_ptr<reference::ListNode<int>> &l2) {
    return reference::AddNumbers(l1, l2);
  }
  
}
