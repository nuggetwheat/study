
#ifndef Books_ElementsOfProgrammingInterviews_ch8_hpp
#define Books_ElementsOfProgrammingInterviews_ch8_hpp

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

namespace study {

  template <typename T>
  struct ListNode {
    T data;
    std::shared_ptr<ListNode<T>> next;
  };

  extern std::shared_ptr<ListNode<int>> MergeTwoSortedLists(std::shared_ptr<ListNode<int>> l1,
                                                            std::shared_ptr<ListNode<int>> l2);

  extern std::shared_ptr<ListNode<int>> ReverseLinkedList(const std::shared_ptr<ListNode<int>> &list);

  extern std::shared_ptr<ListNode<int>> HasCycle(const std::shared_ptr<ListNode<int>> &list);

  extern std::shared_ptr<ListNode<int>> OverlappingNoCycleLists(const std::shared_ptr<ListNode<int>> &l1,
                                                                const std::shared_ptr<ListNode<int>> &l2);

  extern void DeleteFromList(const std::shared_ptr<ListNode<int>> &list);

  extern std::shared_ptr<ListNode<int>> RemoveKthLast(std::shared_ptr<ListNode<int>> &list, int k);

  extern void RemoveDuplicates(const std::shared_ptr<ListNode<int>> &list);

  extern void CyclicallyRightShiftList(std::shared_ptr<ListNode<int>> &list, int k);

  extern void EvenOddMerge(std::shared_ptr<ListNode<int>> &list);

  extern bool IsPalindrome(std::shared_ptr<ListNode<int>> &list);

  extern void PivotList(std::shared_ptr<ListNode<int>> &list, int k);

  extern std::shared_ptr<ListNode<int>> AddNumbers(const std::shared_ptr<ListNode<int>> &l1,
                                                   const std::shared_ptr<ListNode<int>> &l2);

    

}

#endif // Books_ElementsOfProgrammingInterviews_ch8_hpp
