
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <random>
#include <sstream>
#include <vector>

#include "ch7.hpp"

using namespace std;
using namespace study;

namespace {

  default_random_engine g_re(42);
  uniform_int_distribution<unsigned int> g_dist;

  void testIntToString() {
    cout << "[ch7] IntToString" << endl;
    assert(IntToString(5).compare("5") == 0);
    assert(IntToString(12345).compare("12345") == 0);
    assert(IntToString(0).compare("0") == 0);
    assert(IntToString(-23).compare("-23") == 0);
  }

  void testStringToInt() {
    cout << "[ch7] StringToInt" << endl;
    assert(StringToInt("5") == 5);
    assert(StringToInt("12345") == 12345);
    assert(StringToInt("0") == 0);
    assert(StringToInt("-23") == -23);
  }

  void testConvertBase() {
    cout << "[ch7] ConvertBase" << endl;
    string str;
    for (size_t base=2; base<=16; ++base) {
      
      g_re.discard(1);
      for (size_t i=0; i<100; ++i) {
        str.clear();
        for (size_t j=0; j<4; ++j) {
          int digit = (j==0) ? uniform_int_distribution<int>(1, base-1)(g_re) :
            uniform_int_distribution<int>(0, base-1)(g_re);
          if (digit > 9)
            str.append(1, 'A'+(digit-10));
          else
            str.append(1, '0'+digit);
        }
        size_t toBase = uniform_int_distribution<int>(2, 16)(g_re);
        assert(ConvertBase(ConvertBase(str, base, toBase), toBase, base).compare(str) == 0);
      }
    }
  }

  void testSSDecodeColId() {
    cout << "[ch7] SSDecodeColId" << endl;
    assert(SSDecodeColId("D") == 4);
    assert(SSDecodeColId("AA") == 27);
    assert(SSDecodeColId("ZZ") == 702);
  }

  void testReplaceAndRemove() {
    cout << "[ch7] ReplaceAndRemove" << endl;
    assert(ReplaceAndRemove("bbb").empty());
    assert(ReplaceAndRemove("a").compare("dd") == 0);
    assert(ReplaceAndRemove("acaa").compare("ddcdddd") == 0);
    assert(ReplaceAndRemove("acabcab").compare("ddcddcdd") == 0);
  }

  void testIsPalindrome() {
    cout << "[ch7] IsPalindrome" << endl;
    assert(IsPalindrome("A man, a plan, a canal, Panama."));
    assert(IsPalindrome("Able was I, ere I saw Elba!"));
    assert(!IsPalindrome("Ray a Ray"));
  }

  void testReverseWords() {
    cout << "[ch7] ReverseWords" << endl;
    string phrase("ram is costly");
    ReverseWords(&phrase);
    assert(phrase.compare("costly is ram") == 0);
  }

  void testLookAndSay() {
    cout << "[ch7] LookAndSay" << endl;
    assert(LookAndSay(1) == "1");
    assert(LookAndSay(2) == "11");
    assert(LookAndSay(3) == "21");
    assert(LookAndSay(4) == "1211");
    assert(LookAndSay(5) == "111221");
    assert(LookAndSay(6) == "312211");
    assert(LookAndSay(7) == "13112221");
    assert(LookAndSay(8) == "1113213211");
  }

  void testRomanToInteger() {
    cout << "[ch7] RomanToInteger" << endl;
    assert(RomanToInteger("III") == 3);
    assert(RomanToInteger("VI") == 6);
    assert(RomanToInteger("VII") == 7);
    assert(RomanToInteger("XVII") == 17);
    assert(RomanToInteger("XXV") == 25);
    assert(RomanToInteger("XXVII") == 27);
    assert(RomanToInteger("XLI") == 41);
    assert(RomanToInteger("XLVII") == 47);
    assert(RomanToInteger("XXXXXIIIIIIIII") == 59);
    assert(RomanToInteger("LVIIII") == 59);
    assert(RomanToInteger("LIX") == 59);
  }

  void testGetValidIPAddresses() {
    cout << "[ch7] GetValidIPAddresses" << endl;
    auto ret = GetValidIPAddresses("19216811");
    std::vector<std::string> expected =
      { "1.92.168.11", "19.2.168.11", "19.21.68.11", "19.216.8.11",
        "19.216.81.1", "192.1.68.11", "192.16.8.11", "192.16.81.1",
        "192.168.1.1" };
    assert(ret == expected);
  }

  void testSnakeString() {
    cout << "[ch7] SnakeString" << endl;
    assert(SnakeString("Hello, World!") == "e,rHlo ol!lWd");
  }

  void testRle() {
    cout << "[ch7] RunLengthEncode" << endl;
    assert(RleEncode("aaaabcccaa") == "4a1b3c2a");
    assert(RleDecode(RleEncode("aaaabcccaa")) == "aaaabcccaa");
    assert(RleDecode(RleEncode("a")) == "a");
    assert(RleDecode(RleEncode("aabbacccdddeeef")) == "aabbacccdddeeef");
  }

  void testRabinKarp() {
    cout << "[ch7] RabinKarp" << endl;
    const string input("GTTATAGCTGATCGCGGCGTAGCGGCGAAGGCGATTTAGCGGCGTAAGTAGCGGCGATAGCGGCGAAGCGGCGAGCGGCGACGGCGAGGCGAGCGACGAGGTAGCGGCG");
    const string pattern("GTAGCGGCG");
    const vector<int> expected { 18, 47, 100 };
    vector<int> matches;
    int offset;
    int consumed {};
    while ((offset = RabinKarp(input.substr(consumed), pattern)) != -1) {
      matches.push_back(consumed+offset);
      consumed += offset + 1;
    }
    assert(matches == expected);
  }

}

namespace study {

  void ch7_test() {
    testIntToString();
    testStringToInt();
    testConvertBase();
    testSSDecodeColId();
    testReplaceAndRemove();
    testIsPalindrome();
    testReverseWords();
    testLookAndSay();
    testRomanToInteger();
    testGetValidIPAddresses();
    testSnakeString();
    testRle();
    testRabinKarp();
  }

}


