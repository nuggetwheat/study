
#ifndef Language_algorithm_hpp
#define Language_algorithm_hpp

#include <cstdlib>
#include <functional>
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

  template <typename _InputIterator, typename T>
  _InputIterator find(_InputIterator beg, _InputIterator end,
                      const T &value) {
    for (; beg != end; ++beg) {
      if (*beg == value)
        break;
    }
    return beg;
  }

  template <typename _InputIterator, typename _UnaryPredicate>
  _InputIterator find_if(_InputIterator beg, _InputIterator end,
                        _UnaryPredicate pred) {
    for (; beg != end; ++beg) {
      if (pred(*beg))
        break;
    }
    return beg;
  }

  template <typename _InputIterator, typename _UnaryPredicate>
  _InputIterator find_if_not(_InputIterator beg, _InputIterator end,
                             _UnaryPredicate pred) {
    for (; beg != end; ++beg) {
      if (!pred(*beg))
        break;
    }
    return beg;
  }

  template <typename _BinaryPredicate, typename _ForwardIterator, typename _Size, typename _T>
  _ForwardIterator search_n(_ForwardIterator beg, _ForwardIterator end,
                            _Size count, const _T &value, _BinaryPredicate pred) {
    while (beg != end) {
      while (beg != end && !pred(*beg, value))
        ++beg;
      _ForwardIterator base = beg;
      _Size found = count;
      while (beg != end && pred(*beg, value)) {
        ++beg;
        if (--found == 0)
          return base;
      }
    }
    return end;
  }

  template <typename _ForwardIterator, typename _Size, typename _T>
  _ForwardIterator search_n(_ForwardIterator beg, _ForwardIterator end,
                            _Size count, const _T &value) {
    return study::search_n(beg, end, count, value,
                           std::bind(std::equal_to<_T>(), std::placeholders::_1, value));
  }

  template <typename _ForwardIterator1, typename _ForwardIterator2, typename _BinaryPredicate>
  _ForwardIterator1 search(_ForwardIterator1 beg, _ForwardIterator1 end,
                           _ForwardIterator2 searchBeg, _ForwardIterator2 searchEnd,
                           _BinaryPredicate pred) {
    _ForwardIterator1 iter = beg;
    while (iter != end && !pred(*iter, *searchBeg))
      ++iter;
    _ForwardIterator2 piter;
    while (iter != end) {
      auto save_iter = iter;
      piter = searchBeg;
      while (piter != searchEnd && iter != end && pred(*iter, *piter)) {
        ++iter;
        ++piter;
      }
      if (piter == searchEnd)
        return save_iter;
      iter = ++save_iter;
      while (iter != end && !pred(*iter, *searchBeg))
        ++iter;
    }
    return iter;
  }

  template <typename _ForwardIterator1, typename _ForwardIterator2>
  _ForwardIterator1 search(_ForwardIterator1 beg, _ForwardIterator1 end,
                           _ForwardIterator2 searchBeg, _ForwardIterator2 searchEnd) {
    typedef typename std::iterator_traits<_ForwardIterator1>::value_type value_type;
    return study::search(beg, end, searchBeg, searchEnd, std::equal_to<value_type>());
  }

  template <typename _InputIterator1, typename _InputIterator2, typename _BinaryPredicate>
  std::pair<_InputIterator1, _InputIterator2>
  mismatch(_InputIterator1 beg, _InputIterator1 end,
           _InputIterator2 cmpBeg, _BinaryPredicate comp) {
    std::pair<_InputIterator1, _InputIterator2> ret = std::make_pair(beg, cmpBeg);
    while (ret.first != end && comp(*ret.first, *ret.second)) {
      ++ret.first;
      ++ret.second;
    }
    return ret;
  }

  template <typename _InputIterator1, typename _InputIterator2>
  std::pair<_InputIterator1, _InputIterator2>
  mismatch(_InputIterator1 beg, _InputIterator1 end, _InputIterator2 cmpBeg) {
    typedef typename std::iterator_traits<_InputIterator1>::value_type value_type;
    return study::mismatch(beg, end, cmpBeg, std::equal_to<value_type>());
  }
                                                       

}

#endif // Language_algorithm_hpp
