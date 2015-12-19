
#ifndef Books_ElementsOfProgrammingInterviews_ch7_hpp
#define Books_ElementsOfProgrammingInterviews_ch7_hpp

#include <cstdlib>
#include <string>
#include <vector>

namespace study {

  extern std::string IntToString(int x);

  extern int StringToInt(const std::string &s);

  extern std::string ConvertBase(const std::string &s, size_t b1, size_t b2);

  extern int SSDecodeColId(const std::string &col);

  extern std::string ReplaceAndRemove(std::string s);

  extern bool IsPalindrome(const std::string &s);

  extern void ReverseWords(std::string *s);

  extern std::string LookAndSay(int n);

  extern int RomanToInteger(const std::string &str);

  extern std::vector<std::string> GetValidIPAddresses(const std::string &s);

  extern std::string SnakeString(const std::string &s);

  extern std::string RleEncode(const std::string &s);

  extern std::string RleDecode(const std::string &s);

  extern std::string tail(const std::string &file_name, int N);

  extern int RabinKarp(const std::string &text, const std::string &str);

}

#endif // Books_ElementsOfProgrammingInterviews_ch7_hpp
