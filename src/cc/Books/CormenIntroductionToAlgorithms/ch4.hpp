
#ifndef Books_CormenIntroductionToAlgorithms_ch4_hpp
#define Books_CormenIntroductionToAlgorithms_ch4_hpp

#include <cstdlib>
#include <utility>
#include <vector>

namespace study {

  class Trade {
  public:
    std::vector<int>::iterator begin;
    std::vector<int>::iterator end;
    int sum {};
  };

  extern Trade OptimalTradeMaximumSubArray(std::vector<int> &data);

  extern Trade OptimalTradeBruteForce(std::vector<int> &data);


}

#endif // Books_CormenIntroductionToAlgorithms_ch4_hpp
