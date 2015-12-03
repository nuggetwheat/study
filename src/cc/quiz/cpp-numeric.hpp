#ifndef quiz_cpp_numeric_hpp
#define quiz_cpp_numeric_hpp

#include <initializer_list>

#include "quiz.hpp"

/** [TODO]
 * adjacent_difference
 * partial_sum
 */

namespace study {

  const std::initializer_list<Item> cpp_numeric {
    { "Explain the C++ STL algorithm accumulate().",
        R"(
#include <numeric>

template <class InputIterator, class T>
T accumulate(_InputIterator first, InputIterator last, T initValue);

template <class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T initValue,
             BinaryOperation binaryOp);

The first form of the algorithm accumulates values by executing the following
assignment for each element in [first,last) and then returning the accumulated
value.

  initValue = initValue + elem

The second form of the algorithm accumulates values by executing the following
assignment for each element in [first,last) and then returning the accumulated
value.

  initValue = binaryOp(initValue, elem);)" },
    { "Explain the C++ algorithm inner_product().",
        R"(
#include <numeric>

template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 beg1, InputIterator1 end1,
                InputIterator2 beg2, T initValue);

template <class InputIterator1, class InputIterator2, class T,
          class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 beg1, InputIterator1 end1, InputIterator2 beg2,
                T initValue, BinaryOperation1 op1, BinaryOperation2 op2);

The first form computes and returns the inner product of initValue and all
elements in the range [beg1,end1) combined with the elements in the range
starting with beg2.  In particular, it calls the following for all corresponding
elements:

  initValue = initValue + elem1 * elem2

The second form also computes the inner product of initValue and all elements in
the range [beg1,end1) combined with the elements in the range starting with beg2,
but allows you to provide replacement operations for '+' (op1) and '*' (op2).
In particular, it calls the following for all corresponding elements:

  initValue = op1(initValue, op2(elem1, elem2))
)" }
  };

}

#endif // quiz_cpp_numeric_hpp
