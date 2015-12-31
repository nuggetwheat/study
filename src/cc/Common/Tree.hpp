
#ifndef Common_Tree_hpp
#define Common_Tree_hpp

#include <cassert>
#include <memory>

namespace study {

  template <typename T>
  struct BSTNode {
    T data;
    std::unique_ptr<BSTNode<T>> left, right;
  };

  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_1();

}

#endif // Common_Tree_hpp
