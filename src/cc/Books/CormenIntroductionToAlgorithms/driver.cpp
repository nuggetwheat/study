
#include "cutrod.hpp"
#include "quicksort.hpp"
#include "matrix.hpp"

using namespace study;

int main(int argc, char **argv) {

  // quicksort
  test_partition();
  test_nth_element();

  // cutrod
  test_cutrod();

  // matrix
  test_matrix();
}
