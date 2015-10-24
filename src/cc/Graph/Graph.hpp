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

#ifndef Graph_hpp
#define Graph_hpp

#include "Vertex.hpp"

#include <map>
#include <memory>

namespace study {

  class Graph {

  public:

    enum class Type { UNDIRECTED, DIRECTED };

    Graph(const std::string &name, Type type) : m_name(name), m_type(type) {}

    void add_vertex(const std::string &name, Vertex &v) {
      m_vertices[name] = v;
    }

    void add_edge(Edge edge);

    bool has_edge(Edge edge);

    Type type() { return m_type; }

  private:

    std::string m_name;
    Type m_type;
    std::map<std::string, Vertex> m_vertices;
  };

  typedef std::shared_ptr<Graph> GraphPtr;

}

#endif // Graph_hpp
