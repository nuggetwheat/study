
#include "ch4-test.hpp"
#include "cutrod.hpp"
#include "quicksort.hpp"
#include "matrix.hpp"
#include "Graph-test.hpp"

using namespace study;

int main(int argc, char **argv) {

  // ch4
  ch4_test();

  // quicksort
  test_partition();
  test_nth_element();

  // cutrod
  test_cutrod();

  // matrix
  test_matrix();

  // Graph
  test_Graph();
}
