
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>

extern "C" {
#include <termios.h>
#include <unistd.h>
}

#include "cpp-algorithm.hpp"
#include "cpp-numeric.hpp"
#include "design-patterns.hpp"
#include "lock-free.hpp"

using namespace std;
using namespace study;

namespace {

  void waitForKeyPress(const char *prompt = 0) {
    static struct termios oldt, newt;
    if (prompt)
      cout << prompt << flush;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO );  
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  }

}

int main(int argc, const char **argv) {
  vector<Item> items;
  bool sections_loaded {};

  for (int i=1; i<argc; ++i) {
    if (!strcmp(argv[i], "cpp-algorithm")) {
      load_section(items, cpp_algorithm);
      sections_loaded = true;
    }
    else if (!strcmp(argv[i], "cpp-numeric")) {
      load_section(items, cpp_numeric);
      sections_loaded = true;
    }
    else if (!strcmp(argv[i], "design-patterns")) {
      load_section(items, design_patterns);
      sections_loaded = true;
    }
    else if (!strcmp(argv[i], "lock-free")) {
      load_section(items, lock_free);
      sections_loaded = true;
    }
  }

  if (!sections_loaded) {
    load_section(items, cpp_algorithm);
    load_section(items, cpp_numeric);
    load_section(items, design_patterns);
    load_section(items, lock_free);
  }

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();

  default_random_engine dre(seed);
  shuffle(items.begin(), items.end(), dre);

  size_t i {};
  while (true) {
    cout << "\x1B[2J\x1B[H";
    cout << "\n" << items[i].question << "\n";
    waitForKeyPress();
    cout << items[i].answer << "\n\n";
    waitForKeyPress("[Press any key to continue]");
    ++i;
    i %= items.size();
  }
  
}
