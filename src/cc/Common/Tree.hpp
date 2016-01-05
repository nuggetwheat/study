
#ifndef Common_Tree_hpp
#define Common_Tree_hpp

#include <cassert>
#include <memory>

namespace study {

  template <typename T>
  struct BSTNode {
    BSTNode() { }
    BSTNode(T d, BSTNode<T> *p=nullptr) : data(d), parent(p) { }
    T data {};
    std::unique_ptr<BSTNode<T>> left, right;
    BSTNode<T> *parent {};
  };

  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_1(bool include_parent=false);
  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_2(bool include_parent=false);
  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_3a(bool include_parent=false);
  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_3b(bool include_parent=false);
  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_3c(bool include_parent=false);
  extern std::unique_ptr<BSTNode<int>> buildTreeFigure10_4(bool include_parent=false);

}

#endif // Common_Tree_hpp
