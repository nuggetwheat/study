
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  if (argc < 2) {
    cout << "usage: huffman <string-to-encode>" << endl;
    exit(0);
  }

  vector<size_t> count(256, 0);
  const char *text = argv[1];

  for (size_t i=0; text[i]; ++i)
    ++count[text[i]];

  for (size_t i=0; i<256; ++i) {
    if (count[i]) {
      cout << (char)i << ": " << count[i] << "\n";
    }
  }
}
