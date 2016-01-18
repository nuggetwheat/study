
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>

#include "ch11.hpp"

using namespace std;
using namespace study;

namespace study {

  void testHash() {
    cout << "[11.3-4] Hash" << endl;
    assert(Hash(61) == 716);
    assert(Hash(62) == 325);
    assert(Hash(63) == 958);
    assert(Hash(64) == 567);
    assert(Hash(65) == 176);
  }

  const char *test_strings[] = {
    "SquareRoot",
    "MatrixSearch",
    "FindMinMax",
    "FindKthLargest",
    "MailBoxPlacement",
    "FindDuplicateMissing",
    "FindAnagrams",
    "CanFormPalindrome",
    "LCA_optimized",
    "FindNearestRepetition",
    "MoveTowerOfHanoi",
    "NQueens",
    "Permutations",
    "GeneratePowerSet",
    "Combinations",
    (const char *)0
  };

  void testOpenAddressing() {
    cout << "[11.4] OpenAddressing" << endl;
    int i;

    /*
     * Linear probing
     */
    HashTableOpenAddressLinearProbing<int, string> lpTable(30);
    using EntryState = HashTableOpenAddressLinearProbing<int, string>::slot_type;
    vector<EntryState> current_state;

    // Insert data
    for (i=0; test_strings[i]; ++i) {
      lpTable.add(i, test_strings[i]);
      current_state.push_back(EntryState(i, test_strings[i], SlotState::OCCUPIED));
    }

    string str;
    // Verify what was inserted is there
    for (i=0; test_strings[i]; ++i) {
      assert(lpTable.get(i, &str));
      assert(str == test_strings[i]);
    }
    // Verify what wasn't inserted isn't there
    for (; i<100; ++i)
      assert(!lpTable.get(i, &str));
    
    //random_device rd;
    //default_random_engine engine(rd());
    default_random_engine engine(32);
    uniform_int_distribution<int> dist;
    for (i=0; i<1000; ++i) {
      size_t slot = dist(engine) % current_state.size();
      try {
        if (current_state[slot].state == SlotState::OCCUPIED) {
          lpTable.remove(current_state[slot].key);
          current_state[slot].state = SlotState::AVAILABLE;
        }
        else {
          assert(current_state[slot].state == SlotState::AVAILABLE);
          current_state[slot].key = dist(engine);
          assert(current_state[slot].key >= 0);
          current_state[slot].state = SlotState::OCCUPIED;
          lpTable.add(current_state[slot].key, current_state[slot].value);
        }
      }
      catch (std::exception &e) {
        cout << "exception thrown iteration " << i << ": " << e.what() << endl;
        break;
      }
    }

  }

  void ch11_test() {
    testHash();
    testOpenAddressing();
  }

}


