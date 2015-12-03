
#ifndef Books_Sedgewick_Algorithms_tree_hpp
#define Books_Sedgewick_Algorithms_tree_hpp

#include <vector>

namespace study {

  template <typename T>
  class Node {
  public:
    Node(T label) : label_(label) {};
    T label() { return label_; }
    Node *left {};
    Node *right {};
  private:
    T label_ {};
  };

  template <typename T>
  void levelorder_traversal(Node<T> *node, std::vector<T> &output);

  template <typename T>
  void preorder_traversal(Node<T> *node, std::vector<T> &output);

  template <typename T>
  void inorder_traversal(Node<T> *node, std::vector<T> &output);

  template <typename T>
  void postorder_traversal(Node<T> *node, std::vector<T> &output);

  template <typename T>
  void preorder_traversal_nonrecursive(Node<T> *node, std::vector<T> &output);

  template <typename T>
  void inorder_traversal_nonrecursive(Node<T> *node, std::vector<T> &output);

  template <typename T>
  void postorder_traversal_nonrecursive(Node<T> *node, std::vector<T> &output);

}

#include "tree.cpp"

#endif // Books_Sedgewick_Algorithms_tree_hpp
