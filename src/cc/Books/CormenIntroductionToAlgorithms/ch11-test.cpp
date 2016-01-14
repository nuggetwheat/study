
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>

#include "ch11.hpp"

using namespace std;
using namespace study;

namespace study {

  void testHash() {
    cout << "[11.3-4] Hash" << endl;
    assert(Hash(61) == 716);
    assert(Hash(62) == 325);
    assert(Hash(63) == 958);
    assert(Hash(64) == 567);
    assert(Hash(65) == 176);
  }

  void ch11_test() {
    testHash();
  }

}


