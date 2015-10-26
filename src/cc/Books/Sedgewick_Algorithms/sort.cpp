
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

namespace {
  char g_input[] = "ASORTINGEXAMPLE";
  char g_expected_output[] = "AAEEGILMNOPRSTX";

  void populate_input(char *input, int *np) {
    *np = strlen(g_input);
    memcpy(input, g_input, *np);
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

void selection_sort(char *input, int n) {
  cout << "selection sort" << endl;
  for (int i=0; i<(n-1); ++i) {
    int min = i;
    for (int j=i+1; j<n; ++j) {
      if (input[j] < input[min])
        min = j;
    }
    swap(input[i], input[min]);
  }
  input[n] = 0;
}

void insertion_sort(char *input, int n) {
  cout << "insertion sort" << endl;
  int j;
  char v;
  for (int i=1; i<n; ++i) {
    v = input[i];
    j = i;
    while (j > 0 && input[j-1] > v) {
      input[j] = input[j-1];
      j--;
    }
    input[j] = v;
  }
  input[n] = 0;
}

void bubble_sort(char *input, int n) {
  cout << "bubble sort" << endl;
  for (int i=n-1; i>=0; --i) {
    for (int j=0; j<i; ++j) {
      if (input[j] > input[j+1])
        swap(input[j], input[j+1]);
    }
  }
  input[n] = 0;
}

void shell_sort(char *input, int n) {
  cout << "shell sort" << endl;
  int j, h = 1;
  char v;
  while (h < n)
    h = (3*h)+1;
  while (h > 0) {
    h /= 3;
    for (int i=h+1; i<n; ++i) {
      v = input[i];
      j = i;
      while (j >= h && input[j-h] > v) {
        input[j] = input[j-h];
        j -= h;
      }
      input[j] = v;
    }
  }
  input[n] = 0;
}

void distribution_counting(char *input, int n) {
  cout << "distribution counting" << endl;
  int m = 26;
  int *count = new int [m];
  memset(count, 0, m);
  for (int i=0; i<n; ++i)
    count[input[i]-'A']++;
  //for (int i=1; i<m; ++i)
  //count[i] += count[i-1];
  char *output = new char [n+1];
  int j = 0;
  for (int i=0; i<m; i++) {
    while (count[i]) {
      output[j++] = (char)i + 'A';
      count[i]--;
    }
  }
  memcpy(input, output, n);
  input[n] = 0;  
}


int main(int argc, char **argv) {
  char buf[16];
  int n;

  populate_input(buf, &n);
  selection_sort(buf, n);
  verify_output(buf);

  populate_input(buf, &n);
  insertion_sort(buf, n);
  verify_output(buf);

  populate_input(buf, &n);
  bubble_sort(buf, n);
  verify_output(buf);

  populate_input(buf, &n);
  shell_sort(buf, n);
  verify_output(buf);

  populate_input(buf, &n);
  distribution_counting(buf, n);
  verify_output(buf);

  return 0;
}
