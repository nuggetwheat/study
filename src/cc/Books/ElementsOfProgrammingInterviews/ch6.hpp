
#ifndef Books_ElementsOfProgrammingInterviews_ch6_hpp
#define Books_ElementsOfProgrammingInterviews_ch6_hpp

#include <cstdlib>
#include <vector>

namespace study {

  extern void DutchFlagPartition(size_t pivot_index, std::vector<int> *A_ptr);

  extern std::vector<int> PlusOne(std::vector<int> A);

  extern std::vector<int> Multiply(std::vector<int> num1, std::vector<int> num2);

  extern bool CanReachEnd(const std::vector<int> &max_advance_steps);

  extern size_t FewestStepsToEnd(const std::vector<int> &max_advance_steps);

  extern size_t DeleteKey(int key, std::vector<int> *A_ptr);

  extern int DeleteDuplicates(std::vector<int> *A_ptr);

  extern int BuyAndSellStockOnce(const std::vector<int> &prices);

  extern int BuyAndSellStockTwice(const std::vector<int> &prices);

  extern std::vector<int> GeneratePrimes(int n);

  extern void ApplyPermutation(std::vector<int> perm, std::vector<int> *A_ptr);

  extern std::vector<int> NextPermutation(std::vector<int> perm);

  extern std::vector<int> PrevPermutation(std::vector<int> perm);

  extern std::vector<int> ComputeRandomPermutation(int n);

  extern std::vector<int> ComputeRandomSubset(int n, int k);

  extern void RotateMatrix(std::vector<std::vector<int>> *square_matrix_ptr);

}

#endif // Books_ElementsOfProgrammingInterviews_ch6_hpp
