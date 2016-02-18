
#include "ch8.hpp"

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

namespace {
  std::default_random_engine dre;
}

namespace reference {

  std::shared_ptr<ListNode<int>> MergeTwoSortedLists(std::shared_ptr<ListNode<int>> l1,
                                                               std::shared_ptr<ListNode<int>> l2) {
    std::shared_ptr<ListNode<int>> head, tail;
    if ((l1 && l2 && l1->data <= l2->data) || (l1 && !l2)) {
      head = l1;
      tail = head;
      l1 = l1->next;
    }
    else if ((l1 && l2) || (l2 && !l1)) {
      head = l2;
      tail = head;
      l2 = l2->next;
    }

    while (l1 && l2) {
      if (l1->data <= l2->data) {
        tail->next = l1;
        tail = tail->next;
        l1 = l1->next;
      }
      else {
        tail->next = l2;
        tail = tail->next;
        l2 = l2->next;
      }
    }
    if (l1)
      tail->next = l1;
    else if (l2)
      tail->next = l2;
    return head;
  }

  std::shared_ptr<ListNode<int>> ReverseLinkedList(const std::shared_ptr<ListNode<int>> &list) {
    if (!list || !list->next)
      return list;
    shared_ptr<ListNode<int>> lptr = list;
    shared_ptr<ListNode<int>> head = lptr;
    lptr = lptr->next;
    head->next.reset();
    while (lptr) {
      auto tmp = lptr->next;
      lptr->next = head;
      head = lptr;
      lptr = tmp;
    }
    return head;
  }

  std::shared_ptr<ListNode<int>> HasCycle(const std::shared_ptr<ListNode<int>> &list) {
    if (!list || !list->next)
      return nullptr;
    auto slowi = list;
    auto fasti = list;
    fasti = list->next->next;
    while (fasti && slowi != fasti) {
      slowi = slowi->next;
      fasti = fasti->next ? fasti->next->next : fasti->next;
    }
    if (!fasti)
      return nullptr;
    // compute cycle length
    size_t cycle_len {0};
    do {
      slowi = slowi->next;
      cycle_len++;
    } while (slowi != fasti);

    // Find starting node
    slowi = list;
    fasti = list;
    for (size_t i=0; i<cycle_len; ++i)
      fasti = fasti->next;
    while (slowi != fasti) {
      slowi = slowi->next;
      fasti = fasti->next;
    }
    return slowi;
  }

  size_t listLength(const std::shared_ptr<ListNode<int>> &list) {
    size_t length {};
    for (std::shared_ptr<ListNode<int>> ptr = list; ptr; ptr = ptr->next)
      ++length;
    return length;
  }

  std::shared_ptr<ListNode<int>> advance(std::shared_ptr<ListNode<int>> ptr, size_t count) {
    for (size_t i=0; i<count; ++i)
      ptr = ptr->next;
    return ptr;
  }

  std::shared_ptr<ListNode<int>> OverlappingNoCycleLists(const std::shared_ptr<ListNode<int>> &l1,
                                                         const std::shared_ptr<ListNode<int>> &l2) {
    std::shared_ptr<ListNode<int>> ptr1, ptr2;
    auto l1_length = listLength(l1);
    auto l2_length = listLength(l2);
    if (l1_length > l2_length) {
      ptr1 = advance(l1, l1_length - l2_length);
      ptr2 = l2;
    }
    else if (l2_length > l1_length) {
      ptr1 = l1;
      ptr2 = advance(l2, l2_length - l1_length);
    }
    else {
      ptr1 = l1;
      ptr2 = l2;
    }
    while (ptr1 && ptr2 && ptr1 != ptr2) {
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    }
    if (ptr1 && ptr2)
      return ptr1;
    return nullptr;
  }

  void DeleteFromList(const std::shared_ptr<ListNode<int>> &list) {
    assert(list->next);
    std::shared_ptr<ListNode<int>> ptr = list;
    ptr->data = ptr->next->data;
    ptr->next = ptr->next->next;
  }

  std::shared_ptr<ListNode<int>> RemoveKthLast(std::shared_ptr<ListNode<int>> &list, int k) {
    auto first = list;
    while (k--) {
      assert(first);
      first = first->next;
    }
    if (!first) {
      auto ret = list;
      list = list->next;
      return ret;
    }
    auto second = list;
    first = first->next;
    while (first) {
      first = first->next;
      second = second->next;
    }
    auto ret = second->next;
    second->next = second->next->next;
    return ret;
  }

  void RemoveDuplicates(const std::shared_ptr<ListNode<int>> &list) {
    std::shared_ptr<ListNode<int>> ptr = list;
    while (ptr->next) {
      assert(ptr->next->data >= ptr->data);
      if (ptr->next->data == ptr->data)
        ptr->next = ptr->next->next;
      else
        ptr = ptr->next;
    }
  }

  void CyclicallyRightShiftList(std::shared_ptr<ListNode<int>> &list, int k) {
    if (!list)
      return;
    while (true) {
      auto tail = list;
      int len {};
      for (len=1; len<=k; ++len) {
        if (!tail->next)
          break;
        tail = tail->next;
      }
      if (len > k) {
        auto ptr = list;
        while (tail->next) {
          ptr = ptr->next;
          tail = tail->next;
        }
        tail->next = list;
        list = ptr->next;
        ptr->next.reset();
        break;
      }
      // k is greater than list size so try again with k % len
      k %= len;
    }
  }

  void EvenOddMerge(std::shared_ptr<ListNode<int>> &list) {
    if (!list || !list->next)
      return;
    auto ptr1 = list;
    auto list2 = list->next;
    auto ptr2 = list2;
    while (true) {
      if (ptr2->next) {
        // advance ptr1
        ptr1->next = ptr2->next;
        ptr1 = ptr1->next;
        if (ptr1->next) {
          // advance ptr2
          ptr2->next = ptr1->next;
          ptr2 = ptr2->next;
          continue;
        }
      }
      break;
    }
    ptr1->next = list2;
    ptr2->next.reset();
  }

  bool IsPalindrome(std::shared_ptr<ListNode<int>> &list) {
    if (!list)
      return true;
    auto slow = list, fast = list;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    auto back_half = ReverseLinkedList(slow);
    auto front = list;
    auto back = back_half;
    while (front && back) {
      if (front->data != back->data)
        return false;
      front = front->next;
      back = back->next;
    }
    return true;
  }

  void PivotList(std::shared_ptr<ListNode<int>> &list, int k) {
    std::shared_ptr<ListNode<int>> ptr, before, before_tail, equal, equal_tail, after, after_tail;
    ptr = list;
    while (ptr) {
      if (ptr->data < k) {
        if (!before)
          before = before_tail = ptr;
        else {
          before_tail->next = ptr;
          before_tail = before_tail->next;
        }
      }
      else if (ptr->data > k) {
        if (!after)
          after = after_tail = ptr;
        else {
          after_tail->next = ptr;
          after_tail = after_tail->next;
        }
      }
      else {
        if (!equal)
          equal = equal_tail = ptr;
        else {
          equal_tail->next = ptr;
          equal_tail = equal_tail->next;
        }
      }
      ptr = ptr->next;
    }
    list = before ? before : (equal ? equal : after);
    if (before)
      ptr = before_tail;
    if (equal) {
      if (ptr)
        ptr->next = equal;
      ptr = equal_tail;
    }
    if (after) {
      if (ptr)
        ptr->next = after;
      ptr = after_tail;
    }
    ptr->next.reset();
  }

  std::shared_ptr<ListNode<int>> AddNumbers(const std::shared_ptr<ListNode<int>> &l1,
                                            const std::shared_ptr<ListNode<int>> &l2) {
    std::shared_ptr<ListNode<int>> sum_list, sum_iter;
    auto iter1 = l1, iter2 = l2;
    int carry {};
    while (iter1 && iter2) {
      if (!sum_list)
        sum_list = sum_iter = std::make_shared<ListNode<int>>();
      else {
        sum_iter->next = std::make_shared<ListNode<int>>();
        sum_iter = sum_iter->next;
      }
      sum_iter->data = (iter1->data + iter2->data + carry) % 10;
      carry = (iter1->data + iter2->data + carry) / 10;
      iter1 = iter1->next;
      iter2 = iter2->next;
    }
    if (iter1 || iter2) {
      if (!sum_list)
        sum_list = sum_iter = std::make_shared<ListNode<int>>();
      else {
        sum_iter->next = std::make_shared<ListNode<int>>();
        sum_iter = sum_iter->next;
      }
      if (iter1) {
        sum_iter->data = (iter1->data + carry) % 10;
        carry = (iter1->data + carry) / 10;
        iter1 = iter1->next;
        while (iter1) {
          sum_iter->next = std::make_shared<ListNode<int>>();
          sum_iter = sum_iter->next;
          sum_iter->data = iter1->data;
          iter1 = iter1->next;
        }
      }
      else {
        sum_iter->data = (iter2->data + carry) % 10;
        carry = (iter2->data + carry) / 10;
        iter2 = iter2->next;
        while (iter2) {
          sum_iter->next = std::make_shared<ListNode<int>>();
          sum_iter = sum_iter->next;
          sum_iter->data = iter2->data;
          iter2 = iter2->next;
        }
      }
    }
    if (carry) {
      sum_iter->next = std::make_shared<ListNode<int>>();
      sum_iter->next->data = 1;
    }
    return sum_list;
  }
  
}
