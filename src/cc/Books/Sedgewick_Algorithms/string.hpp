
#ifndef Books_Sedgewick_Algorithms_string_hpp
#define Books_Sedgewick_Algorithms_string_hpp

namespace study {

  template <typename ForwardIterator>
  ForwardIterator rabin_karp_search(ForwardIterator beg, ForwardIterator end,
                                    ForwardIterator searchBeg, ForwardIterator searchEnd);

}

#include "string.cpp"

#endif // Books_Sedgewick_Algorithms_string_hpp
