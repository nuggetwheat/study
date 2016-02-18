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

set(SRCS
bits.cpp
bits_test.cpp
ch5.cpp
ch5_test.cpp
ch6.cpp
ch6_test.cpp
ch7.cpp
ch7_test.cpp
ch8.cpp
ch8_test.cpp
ch9.cpp
ch9_test.cpp
ch10.cpp
ch10_test.cpp
ch12.cpp
ch12_test.cpp
ch13.cpp
ch13_test.cpp
ch16.cpp
ch16_test.cpp
ch17.cpp
ch17_test.cpp
ch19.cpp
ch19_test.cpp
reference/ch5.cpp
reference/ch6.cpp
reference/ch7.cpp
reference/ch8.cpp
reference/ch9.cpp
reference/ch10.cpp
reference/ch12.cpp
reference/ch13.cpp
reference/ch16.cpp
reference/ch17.cpp
reference/ch19.cpp
)

add_executable(epi_driver driver.cpp ${SRCS})
target_link_libraries(epi_driver StudyCommon m)

add_test(ElementsOfProgrammingInterviews epi_driver)


