#
# The MIT License (MIT)
# 
# Copyright (c) 2015 Doug Judd
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

add_executable(expr expr.cpp)
#target_link_libraries(expr StudyCommon StudyGraph)

add_executable(expr2 expr2.cpp)
add_executable(gcd gcd.cpp)
add_executable(heapsort heapsort.cpp)
add_executable(huffman huffman.cpp)
add_executable(mergesort mergesort.cpp)
add_executable(quicksort quicksort.cpp)
add_executable(radixsearch radixsearch.cpp)
add_executable(search search.cpp)
add_executable(sort sort.cpp)
add_executable(stringsearch stringsearch.cpp)
add_executable(tree tree.cpp)

add_executable(driver driver.cpp geometric.cpp)


add_test(Sedgewick_Algorithms-expr expr)
add_test(Sedgewick_Algorithms-expr2 expr2)
add_test(Sedgewick_Algorithms-gcd gcd)
add_test(Sedgewick_Algorithms-heapsort heapsort)
add_test(Sedgewick_Algorithms-huffman huffman)
add_test(Sedgewick_Algorithms-mergesort mergesort)
add_test(Sedgewick_Algorithms-quicksort quicksort)
add_test(Sedgewick_Algorithms-radixsearch radixsearch)
add_test(Sedgewick_Algorithms-search search)
add_test(Sedgewick_Algorithms-sort sort)
add_test(Sedgewick_Algorithms-stringsearch stringsearch)
add_test(Sedgewick_Algorithms-tree tree)

add_test(Sedgewick_Algorithms driver)


