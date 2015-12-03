
#undef NDEBUG

#include <cassert>
#include <iostream>

#include "gcd.hpp"
#include "geometric.hpp"
#include "test_sorting.hpp"
#include "test_string.hpp"
#include "test_tree.hpp"

using namespace std;
using namespace study;

int main(int argc, char **argv) {

  // GCD
  assert(gcd(3978, 224944) == 34);
  assert(gcd(133494, 5266116) == 114);
  assert(gcd(2037196, 15792609) == 217);
  assert(gcd(8, 12) == 4);
  assert(gcd(54, 24) == 6);
  assert(gcd(180, 48) == 12);

  // tree
  test_tree();

  // sorting
  test_sorting();

  // string
  test_string();
  
  // geometric
  test_ccw();
  test_intersect();

}
