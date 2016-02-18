
#include "ch7.hpp"
#include "reference/ch7.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

extern "C" {
#include <math.h>
}

using namespace std;

namespace study {
  
  std::string IntToString(int x) {
    return reference::IntToString(x);
  }

  int StringToInt(const std::string &str) {
    return reference::StringToInt(str);
  }

  string ConvertBase(const std::string &s, size_t b1, size_t b2) {
    return reference::ConvertBase(s, b1, b2);
  }

  int SSDecodeColId(const string &col) {
    return reference::SSDecodeColId(col);
  }

  std::string ReplaceAndRemove(std::string s) {
    return reference::ReplaceAndRemove(s);
  }

  bool IsPalindrome(const std::string &s) {
    return reference::IsPalindrome(s);
  }

  void ReverseWords(std::string *s) {
    reference::ReverseWords(s);
  }

  std::string LookAndSay(int n) {
    return reference::LookAndSay(n);
  }

  int RomanToInteger(const std::string &str) {
    return reference::RomanToInteger(str);
  }

  std::vector<std::string> GetValidIPAddresses(const std::string &s) {
    return reference::GetValidIPAddresses(s);
  }

  std::string SnakeString(const std::string &s) {
    return reference::SnakeString(s);
  }

  std::string RleEncode(const std::string &s) {
    return reference::RleEncode(s);
  }

  std::string RleDecode(const std::string &s) {
    return reference::RleDecode(s);
  }

  std::string tail(const std::string &file_name, int N) {
    return reference::tail(file_name, N);
  }

  int RabinKarp(const string &text, const string &str) {
    return reference::RabinKarp(text, str);
  }

}
