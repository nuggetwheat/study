
#include <cassert>

#include "bits.hpp"

namespace {
  
#define COUNT_ONE_BITS_INPUT_SIZE 8

  unsigned int count_one_bits_input[COUNT_ONE_BITS_INPUT_SIZE] = {
    0,
    0xFFFFFFFF,
    0x88888888,
    0xAAAAAAAA,
    0xBBBBBBBB,
    0x1,
    0x80000000,
    0x80000001
  };

  size_t count_one_bits_answers[COUNT_ONE_BITS_INPUT_SIZE] = {
    0,
    32,
    8,
    16,
    24,
    1,
    1,
    2
  };
}

void test_count_one_bits() {

  for (size_t i=0; i<COUNT_ONE_BITS_INPUT_SIZE; ++i) {
    assert(count_one_bits(count_one_bits_input[i]) == count_one_bits_answers[i]);
    assert(count_one_bits_strip_lowest(count_one_bits_input[i]) == count_one_bits_answers[i]);
  }
}
