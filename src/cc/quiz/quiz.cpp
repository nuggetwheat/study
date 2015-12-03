
#include <algorithm>
#include <chrono>
#include <cstdio>
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

  load_section(items, cpp_algorithm);
  load_section(items, cpp_numeric);
  load_section(items, design_patterns);

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
