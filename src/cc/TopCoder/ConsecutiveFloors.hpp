
#ifndef TopCoder_ConsecutiveFloors_hpp
#define TopCoder_ConsecutiveFloors_hpp

#include <string>

namespace study {

  /*
   * Problem Statement
   * 
   * A newly opened hotel has one or more buildings.  Each building has one or
   * more floors.  Different buildings may have a different number of floors.
   * 
   * All the buildings are currently empty. Before any guests move in, the hotel
   * was approached by president Smith. President Smith is planning to rent
   * several consecutive floors of a single hotel building as his office.
   *
   * The president's interns have already researched some possibilities. You are
   * given the results of their research in int[]s x and y. The meaning of these
   * results is as follows: for each valid i, if the president wants to rent
   * exactly x[i] consecutive floors in any single building, there are exactly
   * y[i] distinct ways to do so.
   *
   * You do not know how the hotel looks like. All you have are the interns'
   * notes. Return "Consistent" if there exists a hotel consistent with the
   * research notes. Otherwise, return "Inconsistent".
   * 
   * Definition
   *
   *  Class:ConsecutiveFloors
   *  Method:isConsistent
   *  Parameters:int[], int[]
   *  Returns:String
   *  Method signature:String isConsistent(int[] x, int[] y)
   *  (be sure your method is public)
   *    
   * 
   *Constraints
   *  -x and y will contain between 2 and 50 elements, inclusive.
   *  -x and y will contain the same number of elements.
   *  -Each element of x and y will be between 1 and 10^9, inclusive.
   *  -For each valid i, x[i] will be strictly less than x[i+1].
   *  -For each valid i, y[i] will be strictly greater than y[i+1].
   */
  class ConsecutiveFloors {
  public:
    template <int N>
    std::string isConsistent(int64_t x[N], int64_t y[N]) {
      int buildings = 0;
      int64_t floors = 0;
      for (auto i=N-1; i>=0; --i) {
        if (buildings) {
          int64_t runs_taken = floors - (buildings * (x[i] - 1));
          if (runs_taken > y[i])
            return "Inconsistent";
          int64_t runs_remaining = y[i] - runs_taken;
          int64_t runs_per_building = x[i+1] - x[i];
          int64_t floors_per_building = runs_per_building + x[i] - 1;
          while (runs_remaining) {
            ++buildings;
            if (runs_remaining >= runs_per_building) {
              runs_remaining -= runs_per_building;
              floors += floors_per_building;
            }
            else {
              floors += runs_remaining + x[i] - 1;
              runs_remaining = 0;
            }
          }
        }
        else {
          buildings = 1;
          floors = x[i] + (y[i] - 1);
        }
      }
      return "Consistent";
    }
  };

}

#endif // TopCoder_ConsecutiveFloors_hpp
