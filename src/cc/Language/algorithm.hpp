
#include <cstdlib>
#include <iterator>
#include <utility>

namespace study {

  template <typename InputIterator, typename Func>
  Func for_each(InputIterator begin_iter, InputIterator end_iter, Func f) {
    for (; begin_iter != end_iter; ++begin_iter)
      f(*begin_iter);
    return std::move(f);
  }

  template <typename InputIterator, typename T>
  typename std::iterator_traits<InputIterator>::difference_type
  count(InputIterator begin_iter, InputIterator end_iter, const T &value) {
    typename std::iterator_traits<InputIterator>::difference_type total {};
    for (; begin_iter != end_iter; ++begin_iter)
      if (*begin_iter == value)
        ++total;
    return total;
  }

  template <typename InputIterator, typename _UnaryPred>
  typename std::iterator_traits<InputIterator>::difference_type
  count_if(InputIterator begin_iter, InputIterator end_iter, _UnaryPred pred) {
    typename std::iterator_traits<InputIterator>::difference_type total {};
    for (; begin_iter != end_iter; ++begin_iter)
      if (pred(*begin_iter))
        ++total;
    return total;
  }

  template <typename ForwardIterator>
  ForwardIterator min_element(ForwardIterator beg, ForwardIterator end) {
    if (beg != end) {
      for (ForwardIterator iter = beg; iter != end; ++iter) {
        if (*iter < *beg)
          beg = iter;
      }
    }
    return beg;
  }

  template <typename ForwardIterator, typename _Comparator>
  ForwardIterator min_element(ForwardIterator beg, ForwardIterator end,
                              _Comparator cmp) {
    if (beg != end) {
      for (ForwardIterator iter = beg; iter != end; ++iter) {
        if (cmp(*iter, *beg))
          beg = iter;
      }
    }
    return beg;
  }

  template <typename ForwardIterator>
  ForwardIterator max_element(ForwardIterator beg, ForwardIterator end) {
    if (beg != end) {
      for (ForwardIterator iter = beg; iter != end; ++iter) {
        if (*beg < *iter)
          beg = iter;
      }
    }
    return beg;
  }

  template <typename ForwardIterator, typename _Comparator>
  ForwardIterator max_element(ForwardIterator beg, ForwardIterator end,
                              _Comparator cmp) {
    if (beg != end) {
      for (ForwardIterator iter = beg; iter != end; ++iter) {
        if (cmp(*beg, *iter))
          beg = iter;
      }
    }
    return beg;
  }

  template <typename ForwardIterator>
  std::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator beg, ForwardIterator end) {
    std::pair<ForwardIterator, ForwardIterator> ret(beg, beg);
    if (beg != end) {
      for (; beg != end; ++beg) {
        if (*beg < *ret.first)
          ret.first = beg;
        if (!(*beg < *ret.second))
          ret.second = beg;
      }
    }
    return ret;
  }

  template <typename ForwardIterator, typename _Comparator>
  std::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator beg, ForwardIterator end, _Comparator comp) {
    std::pair<ForwardIterator, ForwardIterator> ret(beg, beg);
    if (beg != end) {
      for (; beg != end; ++beg) {
        if (comp(*beg, *ret.first))
          ret.first = beg;
        if (!(comp(*beg, *ret.second)))
          ret.second = beg;
      }
    }
    return ret;
  }


  extern void test_for_each();
  extern void test_count();
  extern void test_minmax();

}
