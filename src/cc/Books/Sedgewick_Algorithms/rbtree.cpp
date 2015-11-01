#undef NDEBUG

#include <cassert>
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
  Node(int k) : key(k) {};
  Node *left {};
  Node *right {};
  int key;
  bool red {};
};

Node *rotate(int v, Node *y) {
  Node *c, gc;
  c = (v < y->key) ? y->left : c = y->right;
  if (v < c->key) {
    gc = c->left;
    c->left = gc->right;
    gc->right = c;
  }
  else {
    gc = c->right;
    c->right = gc->left;
    gc->left = c;
  }
  if (v < y->key)
    y->left = gc;
  else
    y->right = gc;
  return gc;
}

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
