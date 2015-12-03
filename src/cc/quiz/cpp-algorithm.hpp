#ifndef quiz_cpp_algorithm_hpp
#define quiz_cpp_algorithm_hpp

#include <initializer_list>

#include "quiz.hpp"

/** [TODO]
 * for_each
 * count
 * count_if
 * min_element
 * max_element
 * minmax_element
 * find
 * find_if
 * find_if_not
 * search_n
 * search
 * find_end
 * find_first_of
 * adjacent_find
 * equal
 * is_permutation
 * mismatch
 * lexicographical_compare
 * is_sorted
 * is_sorted_until
 * is_partitioned
 * partition_point
 * is_heap
 * is_heap_until
 * all_of
 * any_of
 * none_of
 * copy
 * copy_if
 * copy_n
 * copy_backward
 * move
 * move_backward
 * transform
 * merge
 * swap_ranges
 * fill
 * fill_n
 * generate
 * generate_n
 * iota
 * replace
 * replace_if
 * replace_copy
 * replace_copy_if
 * remove
 * remove_if
 * remove_copy
 * remove_copy_if
 * unique
 * unique_copy
 * reverse
 * reverse_copy
 * rotate
 * rotate_copy
 * shuffle
 * random_shuffle
 * sort
 * stable_sort
 * partial_sort
 * partial_sort_copy
 * nth_element
 * partition
 * stable_partition
 * partition_copy
 * make_heap
 * push_heap
 * pop_heap
 * sort_heap
 * binary_search
 * includes
 * lower_bound
 * upper_bound
 * equal_range
 * set_union
 * set_intersection
 * set_difference
 * set_symmetric_difference
 * inplace_merge
 */

namespace study {

  const std::initializer_list<Item> cpp_algorithm {
    { "Explain the C++ STL algorithm next_permutation().",
        R"(
#include <algorithm>

template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first,
                      BidirectionalIterator last);

template <class BidirectionalIterator, class Compare>
bool next_permutation(BidirectionalIterator first,
                      BidirectionalIterator last, Compare comp);

Returns false when elements are permuted to normal (ASCENDING lexicographical)
order, otherwise returns true.

next_permutation() changes the order of the elements in [first, last)
according to the next permuation.)" },
    { "Explain the C++ STL algorithm prev_permutation().",
        R"(
#include <algorithm>

template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first,
                      BidirectionalIterator last);

template <class BidirectionalIterator, class Compare>
bool prev_permutation(BidirectionalIterator first,
                      BidirectionalIterator last, Compare comp);

Returns false when elements are permuted to normal (DESCENDING lexicographical)
order, otherwise returns true.

prev_permutation() changes the order of the elements in [first, last)
according to the previous permuation.)" }
  };

}

#endif // quiz_cpp_algorithm_hpp
