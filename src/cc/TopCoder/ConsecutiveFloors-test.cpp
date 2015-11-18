
#include <cassert>
#include <iostream>

#include "ConsecutiveFloors.hpp"

using namespace std;
using namespace study;

namespace {

  int64_t cf_x1[2] = {1, 2};
  int64_t cf_y1[2] = {3, 1};

  int64_t cf_x2[2] = {1, 3};
  int64_t cf_y2[2] = {2, 1};

  int64_t cf_x3[3] = {1, 2, 3};
  int64_t cf_y3[3] = {6, 3, 1};

  int64_t cf_x4[3] = {1, 2, 3};
  int64_t cf_y4[3] = {6, 4, 1};

  int64_t cf_x5[3] = {1, 2, 3};
  int64_t cf_y5[3] = {30, 20, 10};

  int64_t cf_x6[4] = {477381380, 518025930, 570087601, 737384427};
  int64_t cf_y6[4] = {933387341, 532515987, 318113054, 112496297};

  int64_t cf_x7[5] = {308943472, 309514623, 420739506, 433180054, 824938090};
  int64_t cf_y7[5] = {825002165, 692190478, 565185585, 520367469, 109640379};

  int64_t cf_x8[6] = {120488476, 120910581, 191235701, 273389056, 325781420, 732516446};
  int64_t cf_y8[6] = {984130593, 891325429, 628742451, 440622881, 368262567, 198194666};

}


namespace study {

  void test_ConsecutiveFloors() {
    ConsecutiveFloors cf;
    cout << cf.isConsistent<2>(cf_x1, cf_y1) << endl;
    cout << cf.isConsistent<2>(cf_x2, cf_y2) << endl;
    cout << cf.isConsistent<3>(cf_x3, cf_y3) << endl;
    cout << cf.isConsistent<3>(cf_x4, cf_y4) << endl;
    cout << cf.isConsistent<3>(cf_x5, cf_y5) << endl;
    cout << cf.isConsistent<4>(cf_x6, cf_y6) << endl;
    cout << cf.isConsistent<5>(cf_x7, cf_y7) << endl;
    cout << cf.isConsistent<6>(cf_x8, cf_y8) << endl;
  }

}
