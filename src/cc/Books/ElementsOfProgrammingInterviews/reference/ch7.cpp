
#include "ch7.hpp"

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

namespace {
  std::default_random_engine dre;
}

namespace reference {

  std::string IntToString(int x) {
    string str;
    if (x == 0)
      str.append(1, '0');
    else {
      bool isNegative = x < 0;
      x = isNegative ? -x : x;
      while (x) {
        str.insert(str.begin(), '0' + (char)(x % 10));
        x /= 10;
      }
      if (isNegative)
        str.insert(str.begin(), '-');
    }
    return str;
  }

  int StringToInt(const std::string &str) {
    int val {};
    if (!str.empty()) {
      bool negate {};
      size_t i {};
      if (str[i] == '-') {
        negate = true;
        ++i;
      }
      for (; i<str.size(); ++i) {
        assert(str[i] >= '0' && str[i] <= '9');
        val = (val * 10) + (str[i]-'0');
      }
      if (negate)
        val *= -1;
    }
    return val;
  }

  int stringToInt(const string &str, size_t b) {
    int val {};
    if (!str.empty()) {
      for (const auto c : str) {
        if (c >= 'A' && c <= 'F')
          val = (val * b) + (c - 'A') + 10;
        else if (c >= '0' && c <= '9')
          val = (val * b) + (c - '0');
        else
          throw runtime_error("Invalid char");
      }
    }
    return val;
  }

  string intToString(int val, size_t b) {
    string rval;
    char next;
    while (val) {
      auto i = val % b;
      next = (i > 9) ? ('A' + (i-10)) : ('0' + i);
      rval.append(1, next);
      val /= b;
    }
    reverse(rval.begin(), rval.end());
    return rval;
  }

  string ConvertBase(const std::string &s, size_t b1, size_t b2) {
    return intToString(stringToInt(s, b1), b2);
  }

  int SSDecodeColId(const string &col) {
    int id {};
    for (const auto c : col)
      id = (id * 26) + c - 'A' + 1;
    return id;
  }

  std::string ReplaceAndRemove(std::string s) {
    size_t new_len = s.size();
    auto iter = s.begin();
    while (iter != s.end()) {
      if (*iter == 'b') {
        iter = s.erase(iter);
        --new_len;
      }
      else {
        if (*iter == 'a')
          ++new_len;
        ++iter;
      }
    }
    if (new_len > s.size()) {
      int input_offset = (int)s.size() - 1;
      s.resize(new_len);
      int write_offset = (int)s.size() - 1;
      while (input_offset >= 0) {
        if (s[input_offset] == 'a') {
          s[write_offset--] = 'd';
          s[write_offset--] = 'd';
        }
        else
          s[write_offset--] = s[input_offset];
        --input_offset;
      }
    }
    return s;
  }

  bool IsPalindrome(const std::string &s) {
    if (!s.empty()) {
      size_t beg = 0, end = s.size() - 1;
      while (beg < end) {
        while (beg < end && !isalnum(s[beg]))
          ++beg;
        while (end > beg && !isalnum(s[end]))
          --end;
        if (beg < end) {
          if (tolower(s[beg]) == tolower(s[end])) {
            ++beg;
            --end;
          }
          else
            return false;
        }
      }
    }
    return true;
  }

  void ReverseWords(std::string *s) {
    reverse(s->begin(), s->end());
    size_t start = 0, end;
    while ((end = s->find(" ", start)) != string::npos) {
      reverse(s->begin()+start, s->begin()+end);
      start = end+1;
    }
    if (start < s->size())
      reverse(s->begin()+start, s->end());
  }

  std::string lookAndSayNext(const string &input) {
    size_t next {1};
    size_t count {1};
    string output;
    while (next < input.size()) {
      if (input[next] == input[next-1])
        ++count;
      else {
        output += to_string(count) + input[next-1];
        count = 1;
      }
      ++next;
    }
    output += to_string(count) + input[next-1];
    return output;
  }

  std::string LookAndSay(int n) {
    string s("1");
    for (int i=1; i<n; ++i)
      s = lookAndSayNext(s);
    return s;
  }

  int RomanToInteger(const std::string &str) {
    int val {};
    unordered_map<char, int> vmap = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
                                      {'C', 100}, {'D', 500}, {'M', 1000} };
    for (size_t i=0; i<str.size(); ++i) {
      if (i < str.size()-1 && vmap[str[i+1]] > vmap[str[i]]) {
        val += vmap[str[i+1]] - vmap[str[i]];
        ++i;
      }
      else
        val += vmap[str[i]];
    }
    return val;
  }

  bool isValidComponent(int level, const string &comp) {
    if (comp[0] == '0' && (level == 0 || comp.size() > 1))
      return false;
    auto val = stoi(comp);
    return val >= 0 && val < 256;
  }

  std::vector<std::string> GetValidIPAddresses(const std::string &s) {
    std::vector<std::string> valid;
    string first, second, third, fourth;
    for (size_t i=1; i<=3 && i<s.size(); ++i) {
      if (!isValidComponent(0, first=s.substr(0, i)))
        break;
      for (size_t j=1; j<=3 && (i+j)<s.size(); ++j) {
        if (!isValidComponent(1, second=s.substr(i, j)))
          break;
        for (size_t k=1; k<=3 && (i+j+k) < s.size(); ++k) {
          if (!isValidComponent(2, third=s.substr(i+j, k)))
            break;
          if (isValidComponent(3, fourth=s.substr(i+j+k)))
            valid.emplace_back(first + "." + second + "." + third + "." + fourth);
        }
      }
    }
    return valid;
  }

  std::string SnakeString(const std::string &s) {
    string rstr;
    for (size_t i=1; i<s.size(); i+=4)
      rstr.append(1, s[i]);
    for (size_t i=0; i<s.size(); i+=2)
      rstr.append(1, s[i]);
    for (size_t i=3; i<s.size(); i+=4)
      rstr.append(1, s[i]);
    return rstr;
  }

  std::string RleEncode(const std::string &s) {
    string rstr;
    size_t start {};
    if (!s.empty()) {
      for (size_t i=1; i<s.size(); ++i) {
        if (s[i] != s[i-1]) {
          rstr.append(to_string(i-start));
          rstr.append(1, s[i-1]);
          start = i;
        }
      }
      rstr.append(to_string(s.size()-start));
      rstr.append(1, s[start]);
    }
    return rstr;
  }

  std::string RleDecode(const std::string &s) {
    string rstr;
    size_t idx {};
    size_t offset {};
    while (offset < s.size()) {
      auto len = stoi(string(s, offset, s.size()), &idx);
      rstr.append(len, s[offset+idx]);
      offset += ++idx;
    }
    return rstr;
  }

  std::string tail(const std::string &file_name, int N) {
    fstream file_ptr(file_name.c_str());
    file_ptr.seekg(0, ios::end);
    int file_size = file_ptr.tellg(), newline_count = 0;
    string last_N_lines;
    for (int i=0; i<file_size; ++i) {
      file_ptr.seekg(-1 - i, ios::end);
      char c;
      file_ptr.get(c);
      if (c == '\n') {
        if (++newline_count >= N)
          break;
      }
      last_N_lines.append(1, c);
    }
    reverse(last_N_lines.begin(), last_N_lines.end());
    return last_N_lines;
  }

  const int kBase = 128, kMod = 1000003;

  int RabinKarp(const string &text, const string &str) {
    if (str.size() > text.size())
      return -1;
    int t_hash {};
    int s_hash {};
    int power_s {1};
    for (size_t i=0; i<str.size(); ++i) {
      power_s = i ? ((power_s * kBase) % kMod) : 1;
      t_hash = ((t_hash * kBase) + text[i]) % kMod;
      s_hash = ((s_hash * kBase) + str[i]) % kMod;
    }

    for (size_t i=str.size(); i<text.size(); ++i) {
      if (t_hash == s_hash && text.compare(i-str.size(), str.size(), str) == 0)
        return i - str.size();
      t_hash = ((t_hash + kMod) - ((text[i-str.size()] * power_s) % kMod)) % kMod;
      t_hash = ((t_hash * kBase) + text[i]) % kMod;
    }

    if (t_hash == s_hash && text.compare(text.size()-str.size(), str.size(), str) == 0)
      return text.size()-str.size();

    return -1;
  }

}
