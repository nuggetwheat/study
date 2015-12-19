
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>

extern "C" {
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
}

#include "cpp-algorithm.hpp"
#include "cpp-numeric.hpp"
#include "design-patterns.hpp"
#include "lock-free.hpp"
#include "linux.hpp"

#include "foo.hpp"

using namespace std;
using namespace study;

namespace {

  char *sbuf {};
  size_t sbuf_size {};

  const char *markupToEscapeCodes(const char *input) {
    size_t input_len = strlen(input);
    if (input_len*2 > sbuf_size) {
      delete [] sbuf;
      sbuf_size = input_len * 2;
      sbuf = new char [ sbuf_size + 1 ];
    }

    char *optr = sbuf;
    const char *iptr = input;
    const char *ptr;
    while ((ptr = strchr(iptr, '<')) != 0) {
      if (!strncmp(ptr, "<b>", 3)) {
        memcpy(optr, iptr, ptr-iptr);
        optr += (ptr-iptr);
        strcpy(optr, "\033[1m");
        optr += strlen(optr);
        iptr = ptr + 3;
      }
      else if (!strncmp(ptr, "</b>", 4)) {
        memcpy(optr, iptr, ptr-iptr);
        optr += (ptr-iptr);
        strcpy(optr, "\033[0m");
        optr += strlen(optr);
        iptr = ptr + 4;
      }
      else {
        ++ptr;
        memcpy(optr, iptr, ptr-iptr);
        optr += (ptr-iptr);
        iptr = ptr;
      }
    }
    strcpy(optr, iptr);
    return sbuf;
  }

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

  size_t g_terminal_height {};

  void paginateOutput(const char *output, const char *prompt) {
    const char *base = output;
    const char *next = base;
    while (base) {
      for (size_t i=0; next && i<g_terminal_height-1; ++i) {
        next = strchr(next, '\n');
        if (next)
          ++next;
      }
      if (next) {
        cout << markupToEscapeCodes(string(base, next-base).c_str());
        if (*next == 0)
          next = nullptr;
      }
      else
        cout << markupToEscapeCodes(base);
      waitForKeyPress("[Press any key to continue]");
      cout << "\n";
      base = next;
    }
  }

}

int main(int argc, const char **argv) {
  vector<Item> items;
  bool sections_loaded {};

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  g_terminal_height = (size_t)w.ws_row;

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
    else if (!strcmp(argv[i], "linux")) {
      load_section(items, linux);
      sections_loaded = true;
    }
    else if (!strcmp(argv[i], "foo")) {
      load_section(items, foo);
      sections_loaded = true;
    }
    else {
      cout << "usage: quiz [section*]\n";
      cout << "\n";
      cout << "section:\n";
      cout << "\n";
      cout << "  cpp-algorithm ..... Algorithms defined in <algorithm> cpp header\n";
      cout << "  cpp-numeric ....... Algorithms defined in <numeric> cpp header\n";
      cout << "  design-patterns ... Design patterns\n";
      cout << "  lock-free ......... Questions regarding lock free programming\n";
      cout << "  linux ............. Questions about Linux\n";
      cout << endl;
      exit(0);
    }

  }

  if (!sections_loaded) {
    load_section(items, cpp_algorithm);
    load_section(items, cpp_numeric);
    load_section(items, design_patterns);
    load_section(items, lock_free);
    load_section(items, linux);
  }

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();

  default_random_engine dre(seed);
  dre.discard(1);
  shuffle(items.begin(), items.end(), dre);

  size_t i {};
  while (true) {
    cout << "\x1B[2J\x1B[H";
    cout << "\n" << markupToEscapeCodes(items[i].question) << "\n";
    waitForKeyPress();
    paginateOutput(items[i].answer, "[Press any key to continue]");
    ++i;
    i %= items.size();
  }
  
}
