
#ifndef Books_Sedgewick_Algorithms_quicksort_hpp
#define Books_Sedgewick_Algorithms_quicksort_hpp

namespace study {

  template <typename ForwardIterator, typename UnaryPredicate>
  ForwardIterator partition(ForwardIterator beg, ForwardIterator end, UnaryPredicate pred);
  
  template <typename RandomAccessIterator>
  void quicksort(RandomAccessIterator beg, RandomAccessIterator end);

  template <typename RandomAccessIterator>
  void nth_element(RandomAccessIterator beg, RandomAccessIterator nth, RandomAccessIterator end);

}

#include "quicksort.cpp"

#endif // Books_Sedgewick_Algorithms_quicksort_hpp
