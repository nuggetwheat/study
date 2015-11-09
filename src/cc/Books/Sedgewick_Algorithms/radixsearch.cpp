
#undef NDEBUG

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "utility.hpp"

using namespace std;

namespace {

  template <typename K>
  Node<K> *radixtree_insert(K v, Node<K> *x) {
    Node<K> *p {};
    int b = (sizeof(K) * 8) - 1;
    do {
      p = x;
      x = (bits(v, b, 1) == 0) ? x->left : x->right;
      b--;
    } while (x != nullptr);
    x = new Node<K>(v);
    if (bits(v, b+1, 1) == 0)
      p->left = x;
    else
      p->right = x;
    return x;
  }

  template <typename K>
  Node<K> *radixtree_search(K v, Node<K> *x) {
    int b = (sizeof(K) * 8) - 1;
    do {
      x = (bits(v, b, 1) == 0) ? x->left : x->right;
      b--;
    } while (x && x->key != v);
    return x;
  }

  template <typename K>
  Node<K> *radixtrie_insert(K v, Node<K> *x) {
    Node<K> *p {};
    int b = (sizeof(K) * 8) - 1;
    while (x && x->key == 0) {
      p = x;
      x = (bits(v, b, 1) == 0) ? x->left : x->right;
      b--;
    }
    if (x) {
      if (x->key == v)
        return x;
      b++;
      while (bits(v, b, 1) == bits(x->key, b, 1)) {
        if (bits(v, b, 1) == 0) {
          p->left = new Node<K>();
          p = p->left;
        }
        else {
          p->right = new Node<K>();
          p = p->right;
        }
        b--;
      }
      if (bits(x->key, b, 1) == 0) {
        p->left = x;
        x = p->right = new Node<K>(v);
      }
      else {
        p->right = x;
        x = p->left = new Node<K>(v);
      }
    }
    else {
      if (bits(v, b+1, 1) == 0)
        x = p->left = new Node<K>(v);
      else
        x = p->right = new Node<K>(v);
    }
    return x;
  }

  template <typename K>
  Node<K> *radixtrie_search(K v, Node<K> *x) {
    int b = (sizeof(K) * 8) - 1;
    while (x && x->key == 0) {
      x = (bits(v, b, 1) == 0) ? x->left : x->right;
      b--;
    }
    if (x && x->key == v)
      return x;
    return nullptr;
  }

  char g_input[] = "AAEEGILMNOPRSTX";

  template <typename K>
  Node<K> *radixtree_populate() {
    Node<K> *tree = new Node<K>(g_input[0]);
    for (size_t i=1; i<strlen(g_input); ++i)
      radixtree_insert(g_input[i], tree);
    return tree;
  }

  template <typename K>
  Node<K> *radixtrie_populate() {
    Node<K> *trie = new Node<K>();
    for (size_t i=0; i<strlen(g_input); ++i)
      radixtrie_insert(g_input[i], trie);
    return trie;
  }

}

int main(int argc, char **argv) {
  Node<char> *tree = radixtree_populate<char>();

  cout << "radix tree search" << endl;

  // positive tests
  for (size_t i=0; i<strlen(g_input); ++i)
    assert(radixtree_search(g_input[i], tree) != nullptr);

  // negative tests
  for (char v = 'a'; v <= 'z'; ++v)
    assert(radixtree_search(v, tree) == nullptr);

  cout << "radix trie search" << endl;

  Node<char> *trie = radixtrie_populate<char>();

  // positive tests
  for (size_t i=0; i<strlen(g_input); ++i)
    assert(radixtrie_search(g_input[i], trie) != nullptr);

  // negative tests
  for (char v = 'a'; v <= 'z'; ++v)
    assert(radixtrie_search(v, trie) == nullptr);

  return 0;
}
