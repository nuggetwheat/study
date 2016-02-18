
#ifndef Books_ElementsOfProgrammingInterviews_ch8_hpp
#define Books_ElementsOfProgrammingInterviews_ch8_hpp

#include "reference/ch8.hpp"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

namespace study {

  extern std::shared_ptr<reference::ListNode<int>> MergeTwoSortedLists(std::shared_ptr<reference::ListNode<int>> l1,
                                                            std::shared_ptr<reference::ListNode<int>> l2);

  extern std::shared_ptr<reference::ListNode<int>> ReverseLinkedList(const std::shared_ptr<reference::ListNode<int>> &list);

  extern std::shared_ptr<reference::ListNode<int>> HasCycle(const std::shared_ptr<reference::ListNode<int>> &list);

  extern std::shared_ptr<reference::ListNode<int>> OverlappingNoCycleLists(const std::shared_ptr<reference::ListNode<int>> &l1,
                                                                const std::shared_ptr<reference::ListNode<int>> &l2);

  extern void DeleteFromList(const std::shared_ptr<reference::ListNode<int>> &list);

  extern std::shared_ptr<reference::ListNode<int>> RemoveKthLast(std::shared_ptr<reference::ListNode<int>> &list, int k);

  extern void RemoveDuplicates(const std::shared_ptr<reference::ListNode<int>> &list);

  extern void CyclicallyRightShiftList(std::shared_ptr<reference::ListNode<int>> &list, int k);

  extern void EvenOddMerge(std::shared_ptr<reference::ListNode<int>> &list);

  extern bool IsPalindrome(std::shared_ptr<reference::ListNode<int>> &list);

  extern void PivotList(std::shared_ptr<reference::ListNode<int>> &list, int k);

  extern std::shared_ptr<reference::ListNode<int>> AddNumbers(const std::shared_ptr<reference::ListNode<int>> &l1,
                                                   const std::shared_ptr<reference::ListNode<int>> &l2);

    

}

#endif // Books_ElementsOfProgrammingInterviews_ch8_hpp
