
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

}

#endif // Books_ElementsOfProgrammingInterviews_ch12_hpp
