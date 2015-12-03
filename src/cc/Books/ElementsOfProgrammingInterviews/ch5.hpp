
#ifndef Books_ElementsOfProgrammingInterviews_bits_hpp
#define Books_ElementsOfProgrammingInterviews_bits_hpp

#include <cstdlib>

namespace study {

  extern size_t CountOneBitsBruteForce(unsigned int x);
  extern size_t CountOneBitsStripLowest(unsigned int x);
  inline size_t CountOneBits(unsigned int x) {
    return CountOneBitsStripLowest(x);
  }

  extern short ParityBruteForce(unsigned int x);
  extern short ParityStripLowest(unsigned int x);
  inline size_t Parity(unsigned int x) {
    return ParityStripLowest(x);
  }

  extern unsigned long ClosestIntSameBitCount(unsigned long x);
  extern unsigned long ClosestIntSameBitCount2(unsigned long x);


}

#endif // Books_ElementsOfProgrammingInterviews_bits_hpp
