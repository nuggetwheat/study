/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Doug Judd
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Graph/Graph.hpp>
#include <Graph/Utility.hpp>

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace study;

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "usage: " << argv[0] << " <dotfile>" << endl;
    exit(1);
  }

  ifstream input(argv[1]);
  input.seekg(0, ios::end);
  streamsize size = input.tellg();
  input.seekg(0, ios::beg);

  GraphPtr graph;

  vector<char> buffer(size);
  if (input.read(buffer.data(), size)) {
    string dot(buffer.data(), size);
    graph = dot_to_graph(dot);
  }

  return 0;
}
