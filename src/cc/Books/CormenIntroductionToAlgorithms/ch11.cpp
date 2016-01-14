
#include <iostream>
#include <stdexcept>

#include "ch11.hpp"

using namespace std;
using namespace study;

namespace study {

  uint32_t Hash(uint32_t key) {
    return (((uint64_t)key * 2654435769LL) & 0xFFC00000LL) >> 22;
  }

}


