#include <cstdlib>
#include <iostream>

using namespace std;


int gcd(int u, int v) {
  do {
    if (u < v) {
      int t = u;
      u = v;
      v = t;
    }
    //u = u - v;
    u %= v;
    cout << "u = " << u << endl;
  } while (u != 0);
  return v;
}

int gcd(int t, int u, int v) {
  return gcd(gcd(v,u), t);
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "usage: gcd <t> <u> <v>" << endl;
    exit (0);
  }
  int t = atoi(argv[1]);
  int v = atoi(argv[2]);
  int u = atoi(argv[3]);
  int result = gcd(t, u, v);
  cout << "Greatest common divisor of (" << t << "," << u << "," << v << ") is " << result << endl;
}
