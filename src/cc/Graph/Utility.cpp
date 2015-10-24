
#include "Graph.hpp"
#include "Utility.hpp"

#include <Common/String.hpp>

#include <boost/algorithm/string.hpp>

#include <cctype>
#include <stdexcept>
#include <vector>

#include <strings.h>

using namespace std;
using namespace study;

namespace {
  void skip_whitespace(const char *&ptr) {
    while (*ptr && isspace(*ptr))
      ptr++;
  }
  void skip_to_whitespace(const char *&ptr) {
    while (*ptr && !isspace(*ptr))
      ptr++;
  }
  Graph::Type str_to_graphtype(const string &str) {
    if (strcasecmp(str.c_str(), "graph"))
      return Graph::Type::UNDIRECTED;
    else if (strcasecmp(str.c_str(), "digraph"))
      return Graph::Type::DIRECTED;
    throw runtime_error(format("Unrecognized graph type '%s'", str.c_str()));
  }
}

GraphPtr study::dot_to_graph(const std::string &str) {
  GraphPtr graph;
  Graph::Type graph_type {};

  const char *base = str.c_str();
  const char *ptr = base;

  skip_whitespace(ptr);

  base = ptr;
  skip_to_whitespace(ptr);
  if (ptr == base)
    throw runtime_error("Empty graph data");

  graph_type = str_to_graphtype(string(base, ptr-base));

  skip_whitespace(ptr);
  base = ptr;
  if ((ptr = strchr(base, '{')) == nullptr)
    throw runtime_error("Mal-formed dot buffer, no '{' found");

  string name(base, ptr-base);
  boost::trim(name);

  graph = make_shared<Graph>(name, graph_type);

  base = ptr+1;
  const char *tmpbase = base;
  while ((ptr = strchr(tmpbase, '}')) != nullptr) {
    if (*(ptr-1) == '\\')
      tmpbase = ptr+1;
    else
      break;
  }

  if (ptr == nullptr)
    throw runtime_error("Mal-formed dot buffer, no matching '}' found");  

  // Split content into lines
  vector<string> lines;
  string line;
  const char *tmpbase = base;
  while ((ptr = strchr(tmpbase, ';')) != nullptr) {
    if (*(ptr-1) == '\\')
      tmpbase = ptr+1;
    else {
      line = string(base, ptr);
      boost::trim(line);
      lines.push_back(line);
      base = tmpbase = ptr + 1;
    }
  }

  graph
  digraph
  subgraph
  node_name (a-zA-Z0-9_)
  port_name (a-zA-Z0-9_)
  {
  }
  ->
  --
  ;
  [
  ]
  ,
  string
  |
  comment (/* .. */, //)

  

  // ...

  return graph;
}
