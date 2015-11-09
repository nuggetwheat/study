
#undef NDEBUG

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {
  char g_input[] = "ASORTINGEXAMPLE";
  char g_expected_output[] = "AAEEGILMNOPRSTX";

  class Heap {
  public:
    vector<char> data;
    int size;
  };

  void populate_input(Heap &heap) {
    heap.size = strlen(g_input);
    heap.data.reserve(heap.size+1);
    for (size_t i=0; g_input[i]; ++i)
      heap.data.push_back(g_input[i]);
    heap.data.push_back((char)0);
  }

  void verify_output(char *output) {
    if (strcmp(output, g_expected_output)) {
      cout << "   INPUT: " << g_input << "\n";
      cout << "  OUTPUT: " << output << "\n";
      cout << "EXPECTED: " << g_expected_output << "\n";
      cout << flush;
      exit(EXIT_FAILURE);
    }
  }
}

/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

size=7
*/

void downheap(Heap &heap, int k) {
  k++;
  char v = heap.data[k-1];
  while (k <= heap.size/2) {
    int j = k + k;
    if (j < heap.size && heap.data[j-1] < heap.data[j])
      j++;
    if (v >= heap.data[j-1])
      break;
    heap.data[k-1] = heap.data[j-1];
    k = j;
  }
  heap.data[k-1] = v;
}

void heapsort(Heap &heap) {
  for (int k=heap.size/2; k>=0; --k)
    downheap(heap, k);
  do {
    char tmp = heap.data[0];
    heap.data[0] = heap.data[heap.size-1];
    heap.data[heap.size-1] = tmp;
    heap.size--;
    downheap(heap, 0);
  } while (heap.size > 0);
}

int main(int argc, char **argv) {
  Heap heap;

  populate_input(heap);
  cout << "heap sort" << endl;
  heapsort(heap);
  verify_output(&heap.data[0]);

  return 0;
}
