
#ifndef Books_ElementsOfProgrammingInterviews_bits_hpp
#define Books_ElementsOfProgrammingInterviews_bits_hpp

#include <cstdlib>

namespace study {

  extern size_t CountOneBitsBruteForce(unsigned int x);
  extern size_t CountOneBitsStripLowest(unsigned int x);
#if 0
  inline size_t CountOneBits(unsigned int x) {
    return CountOneBitsStripLowest(x);
  }
#endif

  extern short ParityBruteForce(unsigned int x);
  extern short ParityStripLowest(unsigned int x);
#if 0
  inline size_t Parity(unsigned int x) {
    return ParityStripLowest(x);
  }
#endif

  // Swaps bits i and j in x
  extern long SwapBits(long x, int i, int j);

  extern unsigned long ClosestIntSameBitCount(unsigned long x);
  extern unsigned long ClosestIntSameBitCount2(unsigned long x);

  extern unsigned Add(unsigned a, unsigned b);
  extern unsigned Multiply(unsigned x, unsigned y);
  extern unsigned Divide(unsigned x, unsigned y);
  extern double Power(double x, int y);

  extern long Reverse(int x);
  extern bool IsPalindrome(int x);

  extern int UniformRandom(int lower_bound, int upper_bound);

}

#endif // Books_ElementsOfProgrammingInterviews_bits_hpp
