
#ifndef Books_CormenIntroductionToAlgorithms_cutrod_hpp
#define Books_CormenIntroductionToAlgorithms_cutrod_hpp

#include <cstdlib>

namespace study {

  extern int cutrod(int *price, size_t n);
  extern int cutrod_topdown_memoized_aux(int *price, size_t n, int *solved);
  extern int cutrod_topdown_memoized(int *price, size_t n);
  extern int cutrod_bottomup_memoized(int *price, size_t n);

  extern void test_cutrod();

}


#endif // Books_CormenIntroductionToAlgorithms_cutrod_hpp
