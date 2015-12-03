
#include <queue>
#include <stack>

namespace study {

  template <typename T>
  void levelorder_traversal(Node<T> *node, std::vector<T> &output) {
    if (node) {
      std::queue<Node<T> *> node_queue;
      node_queue.push(node);
      while (!node_queue.empty()) {
        node = node_queue.front();
        node_queue.pop();
        output.push_back( node->label() );
        if (node->left)
          node_queue.push(node->left);
        if (node->right)
          node_queue.push(node->right);
      }
    }
  }

  template <typename T>
  void preorder_traversal(Node<T> *node, std::vector<T> &output) {
    if (node) {
      output.push_back(node->label());
      preorder_traversal(node->left, output);
      preorder_traversal(node->right, output);
    }
  }

  template <typename T>
  void inorder_traversal(Node<T> *node, std::vector<T> &output) {
    if (node) {
      inorder_traversal(node->left, output);
      output.push_back(node->label());
      inorder_traversal(node->right, output);
    }
  }

  template <typename T>
  void postorder_traversal(Node<T> *node, std::vector<T> &output) {
    if (node) {
      postorder_traversal(node->left, output);
      postorder_traversal(node->right, output);
      output.push_back(node->label());
    }
  }

  template <typename T>
  void preorder_traversal_nonrecursive(Node<T> *node, std::vector<T> &output) {
    if (node) {
      std::stack<Node<T> *> node_stack;
      node_stack.push(node);
      while (!node_stack.empty()) {
        node = node_stack.top();
        node_stack.pop();
        output.push_back(node->label());
        if (node->right)
          node_stack.push(node->right);
        if (node->left)
          node_stack.push(node->left);
      }
    }
  }

  template <typename T>
  void inorder_traversal_nonrecursive(Node<T> *node, std::vector<T> &output) {
    std::stack<Node<T> *> node_stack;
    while (node) {
      while (node) {
        node_stack.push(node);
        node = node->left;
      }
      while (node == nullptr && !node_stack.empty()) {
        node = node_stack.top();
        node_stack.pop();
        output.push_back(node->label());
        node = node->right;
      }
    }
  }

  template <typename T>
  void postorder_traversal_nonrecursive(Node<T> *node, std::vector<T> &output) {
    if (node) {
      std::stack<Node<T> *> first_stack;
      std::stack<Node<T> *> second_stack;
      first_stack.push(node);
      while (!first_stack.empty()) {
        node = first_stack.top();
        first_stack.pop();
        second_stack.push(node);
        if (node->left)
          first_stack.push(node->left);
        if (node->right)
          first_stack.push(node->right);
      }
      while (!second_stack.empty()) {
        output.push_back(second_stack.top()->label());
        second_stack.pop();
      }
    }
  }

}


#if 0

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

class Node {
public:
  Node(const string &label) : m_label(label) {};
  void visit() { cout << m_label << " "; }
  Node *left {};
  Node *right {};
private:
  string m_label {};
};

void recursive_preorder(Node *node) {
  if (node) {
    node->visit();
    recursive_preorder(node->left);
    recursive_preorder(node->right);
  }
}

void recursive_inorder(Node *node) {
  if (node) {
    recursive_inorder(node->left);
    node->visit();
    recursive_inorder(node->right);
  }
}

void recursive_postorder(Node *node) {
  if (node) {
    recursive_postorder(node->left);
    recursive_postorder(node->right);
    node->visit();
  }
}

void nonrecursive_preorder(Node *node) {
  stack<Node *> state;
  state.push(node);
  while (!state.empty()) {
    node = state.top();
    state.pop();
    node->visit();
    if (node->right)
      state.push(node->right);
    if (node->left)
      state.push(node->left);
  }
}

void nonrecursive_inorder(Node *node) {
  stack<Node *> state;

  while (node) {

    while (node) {
      state.push(node);
      node = node->left;
    }

    while (node == 0 && !state.empty()) {
      node = state.top();
      state.pop();
      node->visit();
      node = node->right;
    }

  }
}

void nonrecursive_postorder(Node *node) {
  stack<Node *> state;
  stack<Node *> visit;

  while (node) {

    visit.push(node);
    if (node->left)
      state.push(node->left);
    if (node->right)
      state.push(node->right);

    if (!state.empty()) {
      node = state.top();
      state.pop();
    }
    else
      node = 0;
  }

  while (!visit.empty()) {
    node = visit.top();
    visit.pop();
    node->visit();
  }
}


int main(int argc, char **argv) {
  Node *tree, *node;

  tree = new Node("P");
  tree->left = new Node("M");
  node = tree->left;
  node->left = new Node("S");
  node = node->left;
  node->left = new Node("A");
  node->right = new Node("A");
  tree->right = new Node("L");
  node = tree->right;
  node->right = new Node("E");
  node = node->right;
  node->right = new Node("R");
  node = node->right;
  node->left = new Node("T");
  node->right = new Node("E");
  node = node->right;
  node->left = new Node("E");

  cout << "recursive:" << endl;
  recursive_preorder(tree);
  cout << endl;
  recursive_inorder(tree);
  cout << endl;
  recursive_postorder(tree);
  cout << endl;

  cout << "nonrecursive:" << endl;
  nonrecursive_preorder(tree);
  cout << endl;
  nonrecursive_inorder(tree);
  cout << endl;
  nonrecursive_postorder(tree);
  cout << endl;

  return 0;
}

#endif
