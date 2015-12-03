
#include <algorithm>
#include <iterator>
#include <limits>
#include <type_traits>

namespace study {

  template <typename ForwardIterator>
  ForwardIterator rabin_karp_search(ForwardIterator beg, ForwardIterator end,
                                    ForwardIterator searchBeg, ForwardIterator searchEnd) {
    const uint64_t q = 999999999989LL;
    const uint64_t d = 1 << (sizeof(typename std::iterator_traits<ForwardIterator>::value_type)*8);
    uint64_t dM = 1;
    uint64_t phash = 0;
    size_t plen {};
    ForwardIterator iter;

    for (iter = searchBeg; iter != searchEnd; ++iter) {
      if (iter != searchBeg)
        dM = (d*dM) % q;
      phash = ((phash*d) + *iter) % q;
      ++plen;
    }

    uint64_t thash = 0;
    for (iter = beg; plen > 0 && iter != end; ++iter,--plen)
      thash = ((thash*d) + *iter) % q;

    // Check if pattern is longer than input text
    if (plen)
      return end;

    while (thash != phash && iter != end) {
      thash = ((thash + (d*q)) - (*beg++*dM)) % q;
      thash = ((thash*d) + *iter++) % q;
    }
    
    return (thash == phash) ? beg : end;
  }
  

}
