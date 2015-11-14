
#ifndef Books_CormenIntroductionToAlgorithms_quicksort_hpp
#define Books_CormenIntroductionToAlgorithms_quicksort_hpp

#include <cstdlib>

namespace study {

template <typename T>
size_t partition(T *input, size_t begin, size_t end);

template <typename T>
T nth_element(T *input, size_t begin, size_t end, size_t i);

}

#include "quicksort.cpp"

extern void test_partition();
extern void test_nth_element();

#endif // Books_CormenIntroductionToAlgorithms_quicksort_hpp
