
#ifndef Books_ElementsOfProgrammingInterviews_reference_ch13_hpp
#define Books_ElementsOfProgrammingInterviews_reference_ch13_hpp

#include "Common/Tree.hpp"

#include <cstdlib>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace reference {
  
  extern std::vector<std::vector<std::string>> FindAnagrams(const std::vector<std::string> &dictionary);

  extern bool CanFormPalindrome(const std::string &word);

  extern study::BSTNode<int> *LCA_optimized(const std::unique_ptr<study::BSTNode<int>> &node0,
                                            const std::unique_ptr<study::BSTNode<int>> &node1);

  extern int FindNearestRepetition(const std::vector<std::string> &paragraph);

  

}

#endif // Books_ElementsOfProgrammingInterviews_reference_ch13_hpp
