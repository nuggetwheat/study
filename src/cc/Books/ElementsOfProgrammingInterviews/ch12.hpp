
#ifndef Books_ElementsOfProgrammingInterviews_ch12_hpp
#define Books_ElementsOfProgrammingInterviews_ch12_hpp

#include "Common/Tree.hpp"

#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace study {
  
  extern int BinarySearch(const std::vector<int> &data, int t);

  extern int SearchFirstOfK(const std::vector<int> &data, int k);

  extern int SearchFirstLargerOfK(const std::vector<int> &data, int k);

  extern int SearchEntityEqualToItsIndex(const std::vector<int> &data);

  extern int SearchSmallest(const std::vector<int> &data);

  extern int SearchSmallestWithRepeated(const std::vector<int> &data);

  extern int SquareRoot(int k);

  extern double SquareRoot(double k);

  extern bool MatrixSearch(const std::vector<std::vector<int>> &A, int x);

  extern std::pair<int, int> FindMinMax(const std::vector<int> &A);

  extern int FindKthLargest(std::vector<int> *A_ptr, size_t k);

  extern double MailBoxPlacement(const std::vector<int> &A);  

  extern std::pair<int, int> FindDuplicateMissing(const std::vector<int> &A);

}

#endif // Books_ElementsOfProgrammingInterviews_ch12_hpp
