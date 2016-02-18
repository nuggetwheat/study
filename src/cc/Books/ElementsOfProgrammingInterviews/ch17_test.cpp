
#undef NDEBUG

#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "ch17.hpp"

using namespace std;
using namespace study;

namespace {

  void testFibonacci() {
    cout << "[ch17] Fibonacci" << endl;
    vector<size_t> expected {0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584};
    vector<size_t> result;
    for (size_t i=1; i<20; ++i)
      result.push_back(FibonacciRecursive(i));
    assert(result == expected);
    result.clear();
    for (size_t i=1; i<20; ++i)
      result.push_back(FibonacciDynamic(i));
    assert(result == expected);
  }

  void testFindMaximumSubarray() {
    cout << "[ch17] FindMaximumSubarray" << endl;
    vector<int> input {904, 40, 523, 12, -335, -385, -124, 481, -31};
    auto result = FindMaximumSubarray(input);
    assert(result == make_pair(0, 4));
    input.insert(input.begin(), -456);
    result = FindMaximumSubarray(input);
    assert(result == make_pair(1, 5));
  }

  void testCountCombinationsAndPermutations() {
    cout << "[ch17] CountCombinationsAndPermutations" << endl;
    assert(CountCombinations(12, {2,3,7}) == 4);
    assert(CountPermutations(12, {2,3,7}) == 18);
  }

  void testEditDistance() {
    cout << "[ch17] EditDistance" << endl;
    assert(EditDistance("Carthorse", "Orchestra") == 8);
    assert(EditDistance("Orchestra", "Carthorse") == 8);
    assert(EditDistance("Carthorse", "horse") == 4);
    assert(EditDistance("Orchestra", "") == 9);
    assert(EditDistance("Orchestra", "Orchestra") == 0);
    assert(EditDistanceOptimized("Carthorse", "Orchestra") == 8);
    assert(EditDistanceOptimized("Orchestra", "Carthorse") == 8);
    assert(EditDistanceOptimized("Carthorse", "horse") == 4);
    assert(EditDistanceOptimized("Orchestra", "") == 9);
    assert(EditDistanceOptimized("Orchestra", "Orchestra") == 0);
    assert(MinimumRemovalsToPalindrome("anuja") == 2);
    assert(MinimumRemovalsToPalindrome("amphibian") == 4);
    assert(MinimumRemovalsToPalindrome("applesauce") == 6);
    assert(MinimumRemovalsToPalindrome("rotator") == 0);
  }

  void testNumberOfWaysToTraverse2DArray() {
    cout << "[ch17] NumberOfWaysToTraverse2DArray" << endl;
    assert(NumberOfWaysToTraverse2DArray(5, 5) == 70);
    assert(NumberOfWaysToTraverse2DArrayOptimized(5, 5) == 70);
  }

  void testCountMonotone() {
    cout << "[ch17] CountMonotone" << endl;
    assert(CountMonotone(3) == 10);
    assert(CountMonotoneOptimized(3) == 10);
  }


  void testMaximizeFishing() {
    cout << "[ch17] MaximizeFishing" << endl;
    vector<vector<int>> sea;
    sea.push_back({0, 0, 1, 2, 0});
    sea.push_back({0, 2, 5, 0, 1});
    sea.push_back({0, 1, 3, 1, 3});
    sea.push_back({5, 0, 2, 0, 5});
    sea.push_back({2, 3, 1, 0, 5});
    assert(MaximizeFishing(sea) == 24);
  }

  void testMatch() {
    cout << "[ch17] Match" << endl;
    vector<vector<int>> matrix;
    matrix.push_back({1, 2, 3});
    matrix.push_back({3, 4, 5});
    matrix.push_back({5, 6, 7});
    vector<int> ss { 1, 3, 4, 6 };
    assert(Match(matrix, ss));
  }

  void testKnapsack() {
    cout << "[ch17] Knapsack" << endl;
    vector<reference::Item> items;
    items.push_back({65,20});
    items.push_back({35,8});
    items.push_back({245,60});
    items.push_back({195,55});
    items.push_back({65,40});
    items.push_back({150,70});
    items.push_back({275,85});
    items.push_back({155,25});
    items.push_back({120,30});
    items.push_back({320,65});
    items.push_back({75,75});
    items.push_back({40,10});
    items.push_back({200,95});
    items.push_back({100,50});
    items.push_back({220,40});
    items.push_back({99,10});
    assert(study::Knapsack(130, items) == 695);
    assert(study::KnapsackOptimized(130, items) == 695);
  }

  void testMinimizeDifference() {
    cout << "[ch17] MinimizeDifference" << endl;
    vector<int> values {65, 35, 245, 195, 65, 150, 275, 155,
        120, 320, 75, 40, 200, 100, 220, 99};
    assert(MinimizeDifference(values) == 1);
  }

  void testWordBreaking() {
    cout << "[ch17] WordBreaking" << endl;
    unordered_set<string> dict { "bed", "bath", "and", "beyond" };
    auto result = WordBreaking("bedbathandbeyond", dict);
    assert(result == vector<string>({ "bed", "bath", "and", "beyond" }));
    result = WordBreakingOptimized("bedbathandbeyond", dict);
    assert(result == vector<string>({ "bed", "bath", "and", "beyond" }));
    dict.insert("bat");
    dict.insert("hand");
    result = WordBreaking("bedbathandbeyond", dict);
    assert(result == vector<string>({ "bed", "bat", "hand", "beyond" }));
    result = WordBreakingOptimized("bedbathandbeyond", dict);
    assert(result == vector<string>({ "bed", "bat", "hand", "beyond" }));
  }

  void testFindMinimumTotal() {
    cout << "[ch17] FindMinimumTotal" << endl;
    vector<vector<int>> triangle;
    triangle.push_back({1});
    triangle.push_back({1, 1});
    triangle.push_back({1, 2, 1});
    triangle.push_back({1, 3, 3, 1});
    triangle.push_back({1, 4, 6, 4, 1});
    assert(FindMinimumTotal(triangle) == 5);
    triangle.clear();
    triangle.push_back({232});
    triangle.push_back({25, 0});
    triangle.push_back({43, 68, 59});
    triangle.push_back({39, 2, 59, 64});
    triangle.push_back({2, 97, 5, 294, 8});
    triangle.push_back({9, 18, 804, 77, 9, 2});
    assert(FindMinimumTotal(triangle) == 350);
  }

  void testPickUpCoins() {
    cout << "[ch17] PickUpCoins" << endl;
    vector<int> input { 25, 5, 10, 5, 10, 5, 10, 25, 1, 25, 1, 25, 1, 25, 5, 10 };
    assert(PickUpCoins(input) == 140);
  }

  void testNumberOfSteps() {
    cout << "[ch17] NumberOfSteps" << endl;
    assert(NumberOfSteps(4, 2) == 5);
    assert(NumberOfStepsOptimized(4, 2) == 5);
  }

  void testHouseMajority() {
    cout << "[ch17] HouseMajority" << endl;
    vector<double> prob { 0.0266434, 0.126322, 0.537865, 0.605799, 0.419114, 
        0.329313, 0.37618, 0.292569, 0.365618, 0.996458, 0.543059, 0.943447, 
        0.134116, 0.0100874, 0.241234, 0.428602, 0.817549, 0.421819, 0.225297, 
        0.883827, 0.052011, 0.664029, 0.809916, 0.18724, 0.909046, 0.00428791, 
        0.197956, 0.178613, 0.645394, 0.9106, 0.706934, 0.500416, 0.985247, 
        0.800957, 0.256027, 0.373368, 0.880589, 0.246185, 0.512991, 0.619131, 
        0.767342, 0.10244, 0.492882, 0.770325, 0.00378227, 0.721221, 0.166617, 
        0.203412, 0.0362905, 0.785707, 0.174136, 0.612163, 0.551847, 0.230622, 
        0.253717, 0.99251, 0.785451, 0.783846, 0.876104, 0.164956, 0.549652, 
        0.105812, 0.373366, 0.122793, 0.668417, 0.626797, 0.600519, 0.777091, 
        0.104217, 0.733829, 0.648627, 0.368317, 0.572351, 0.721147, 0.0834295, 
        0.14833, 0.37917, 0.26105, 0.38394, 0.44785, 0.966123, 0.369182, 
        0.737427, 0.805089, 0.149307, 0.413575, 0.734737, 0.845067, 0.481913, 
        0.140346, 0.0838437, 0.93613, 0.228116, 0.751695, 0.29548, 0.00951269, 
        0.796125, 0.359081, 0.626361, 0.0664648, 0.798493, 0.154299, 0.651082, 
        0.959796, 0.936913, 0.283782, 0.647397, 0.0974467, 0.615176, 0.659561, 
        0.0982626, 0.136679, 0.707313, 0.706382, 0.574083, 0.551157, 0.932701, 
        0.782379, 0.823023, 0.421937, 0.109943, 0.445858, 0.144839, 0.276278, 
        0.704792, 0.601765, 0.568989, 0.221293, 0.783127, 0.492233, 0.296403, 
        0.332925, 0.953037, 0.954273, 0.344152, 0.444905, 0.504422, 0.99236, 
        0.755103, 0.811953, 0.375617, 0.693667, 0.534503, 0.167119, 0.661576, 
        0.332797, 0.6173, 0.135609, 0.637775, 0.4368, 0.466159, 0.898292, 
        0.0451389, 0.276839, 0.409052, 0.842123, 0.461583, 0.133228, 0.499475, 
        0.62227, 0.190908, 0.869759, 0.67833, 0.103426, 0.0172043, 0.998672, 
        0.194515, 0.325114, 0.197214, 0.281777, 0.705186, 0.407836, 0.73293, 
        0.141093, 0.504354, 0.0441261, 0.0200555, 0.411494, 0.371397, 0.0157405, 
        0.418629, 0.4699, 0.556144, 0.810554, 0.847372, 0.90657, 0.146905, 
        0.339345, 0.461457, 0.952857, 0.985679, 0.0604319, 0.784617, 0.828338, 
        0.0965374, 0.270547, 0.309964, 0.909303, 0.430365, 0.786673, 0.587544, 
        0.528301, 0.826916, 0.554407, 0.726563, 0.533882, 0.464668, 0.76857, 
        0.980075, 0.421702, 0.834187, 0.692374, 0.172016, 0.81438, 0.475141, 
        0.41253, 0.874058, 0.406304, 0.0563586, 0.879924, 0.293555, 0.500878, 
        0.564541, 0.495988, 0.863826, 0.682916, 0.898695, 0.530563, 0.135997, 
        0.362449, 0.797053, 0.796511, 0.419413, 0.162411, 0.870867, 0.690002, 
        0.570462, 0.203947, 0.238994, 0.300979, 0.190561, 0.888452, 0.529465, 
        0.990079, 0.844232, 0.0214035, 0.737513, 0.575801, 0.152381, 0.768633, 
        0.58722, 0.609257, 0.219813, 0.138285, 0.570617, 0.180518, 0.869485, 
        0.353813, 0.475853, 0.558741, 0.309158, 0.274011, 0.666372, 0.458368, 
        0.773084, 0.778849, 0.935414, 0.742019, 0.593845, 0.282529, 0.447453, 
        0.39919, 0.395155, 0.41558, 0.736347, 0.361649, 0.925354, 0.450573, 
        0.899694, 0.0739139, 0.854325, 0.608456, 0.583638, 0.375675, 0.920408, 
        0.740597, 0.265927, 0.24993, 0.738631, 0.956128, 0.0302439, 0.773633, 
        0.619321, 0.590125, 0.157791, 0.111194, 0.631636, 0.456501, 0.180359, 
        0.664701, 0.427902, 0.0370424, 0.492263, 0.0303866, 0.649954, 0.646727, 
        0.509464, 0.0688697, 0.947982, 0.678639, 0.124848, 0.519049, 0.758034, 
        0.754019, 0.785456, 0.680873, 0.287316, 0.720452, 0.754464, 0.421336, 
        0.589404, 0.40602, 0.689631, 0.686152, 0.135195, 0.487726, 0.762733, 
        0.314747, 0.779786, 0.866498, 0.673784, 0.582342, 0.458012, 0.198099, 
        0.8486, 0.0649657, 0.235294, 0.0388104, 0.0846668, 0.719295, 0.503778, 
        0.568203, 0.593133, 0.610203, 0.619858, 0.0373709, 0.523259, 0.342258, 
        0.529263, 0.609705, 0.388889, 0.525706, 0.33819, 0.472224, 0.000358171, 
        0.296812, 0.0779176, 0.609275, 0.228554, 0.21417, 0.0180567, 0.613078, 
        0.614358, 0.948816, 0.136476, 0.719347, 0.160787, 0.779031, 0.899021, 
        0.0912298, 0.295848, 0.0735567, 0.962185, 0.724512, 0.722321, 0.224818, 
        0.550222, 0.390261, 0.975815, 0.414747, 0.1695, 0.0423491, 0.277552, 
        0.926509, 0.804996, 0.734713, 0.760065, 0.620523, 0.265414, 0.675101, 
        0.713569, 0.205517, 0.0133607, 0.138617, 0.425488, 0.0315377, 0.353687, 
        0.215548, 0.128328, 0.295013, 0.751564, 0.978817, 0.74416, 0.997455, 
        0.531246, 0.131948, 0.119481, 0.511846, 0.625428, 0.814175, 0.97259, 
        0.630807, 0.260116, 0.370136, 0.9077, 0.277817, 0.0442744, 0.625121, 
        0.5461, 0.501605, 0.623352, 0.221112, 0.53227, 0.938509, 0.470608, 
        0.106393, 0.454214, 0.938462, 0.979728, 0.944882, 0.803141, 0.246913, 
        0.492454, 0.167172, 0.841597 };
    stringstream ss;
    ss << HouseMajority(prob, 435);
    assert(ss.str() == "0.501067");
  }

  void testFindPrettyPrinting() {
    cout << "[ch17] FindPrettyPrinting" << endl;
    vector<string> W { "I", "have", "inserted", "a", "large", "number", "of",
        "new", "examples", "from", "the", "papers", "for", "the",
        "Mathematical", "Tripos", "during", "the", "last", "twenty", "years,",
        "which", "should", "be", "useful", "to", "Cambridge", "students." };
    assert(FindPrettyPrinting(W, 36, true) == 76);
    assert(FindPrettyPrinting(W, 36, false) == 12);
  }

  void testLongestNondecreasingSubsequence() {
    cout << "[ch17] LongestNondecreasingSubsequence" << endl;
    vector<int> input { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9 };
    vector<int> expected { 0, 8, 12, 14 };
    assert(LongestNondecreasingSubsequence(input) == expected);
  }

  
}


namespace study {

  void ch17_test() {
    testFibonacci();
    testFindMaximumSubarray();
    testCountCombinationsAndPermutations();
    testEditDistance();
    testNumberOfWaysToTraverse2DArray();
    testCountMonotone();
    testMaximizeFishing();
    testMatch();
    testKnapsack();
    testMinimizeDifference();
    testWordBreaking();
    testFindMinimumTotal();
    testPickUpCoins();
    testNumberOfSteps();
    testHouseMajority();
    testFindPrettyPrinting();
    testLongestNondecreasingSubsequence();
  }

}


